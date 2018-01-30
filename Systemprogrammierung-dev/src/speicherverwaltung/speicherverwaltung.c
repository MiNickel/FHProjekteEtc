/*!
 * \file speicherverwaltung.c
 * \brief Implementierung der Speicherverwaltung
 */
#include "speicherverwaltung/speicherverwaltung.h"

#ifdef MALLOCSPLIT
	#define SPLIT 1
#else
	#define SPLIT 0
#endif

memblock *freemem;
char mempool[];

void init_heap(void) {
	static int initialized = 0;
	if (!initialized) {
		freemem = (memblock *) mempool;
		freemem->size = MEM_POOL_SIZE - sizeof(memblock);
		freemem->next = NULL;
		initialized = 1;
	}
}

void *cm_malloc(size_t size) {
	init_heap();
	
	if (size <= 0) {
		return NULL;
	}
	
	memblock *nextfree = freemem;
	memblock *beforenextfree;
	while (nextfree && nextfree->size < size) {
		beforenextfree = nextfree;
		nextfree = nextfree->next;
	}
	
	if ((char *) nextfree < mempool || (char *) nextfree > mempool + MEM_POOL_SIZE) {
		return NULL;
	}
	
	if (nextfree) {
		if (SPLIT) {
			if (nextfree->size > size + 2*sizeof(memblock) + 32) {
				memblock *newfree = (memblock *)((char *)nextfree + sizeof(memblock) + size);
				newfree->next = nextfree->next;
				newfree->size = nextfree->size - (size + sizeof(memblock));
				if (nextfree == freemem) {
					freemem = newfree;
				} else {
					beforenextfree->next = newfree;
				}
				nextfree->size = size;
			} else {
				if (nextfree == freemem) {
					freemem = freemem->next;
				} else {
					beforenextfree->next = nextfree->next;
				}
		}
		} else {
			if (nextfree == freemem) {
				freemem = freemem->next;
			} else {
				beforenextfree->next = nextfree->next;
			}
		}
		nextfree->next = (memblock *)MAGIC_INT;
		return nextfree+1;
	}
	return NULL;
}

void cm_free(void *ptr) {
	if(ptr && (char *)ptr >= mempool + sizeof(memblock)&& (char *)ptr < mempool + MEM_POOL_SIZE) {
		memblock *mem_ptr = (memblock *)ptr;
		mem_ptr--;
		if (mem_ptr->next == (memblock *)MAGIC_INT) {
			mem_ptr->next = freemem;
			freemem = mem_ptr;
		}
	}	
}

memblock *get_prev_block(memblock *ptr) {
	memblock *currentPtr = freemem;
	memblock *prevPtr = NULL;
	while (currentPtr && currentPtr != ptr) {
		prevPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	if (currentPtr){ 
		return prevPtr;
	} 
	return NULL;
}

void cm_defrag(void) {
	memblock *currentBlock = freemem;
	memblock *nextBlock;
	memblock *prevNextBlock;
	memblock *prevcurrentblock = currentBlock;
	int notfound;
	size_t size;
	
	while (currentBlock) {
		notfound = 1;
		nextBlock = freemem;
		prevNextBlock = nextBlock;
		size = currentBlock->size;
		
		while (nextBlock && notfound) {
			if (nextBlock == (memblock *)((char *)(currentBlock + 1) + currentBlock->size)) {
				notfound = 0;
				
				if (nextBlock->next != (memblock *) MAGIC_INT) {
					currentBlock->size += sizeof(memblock) + nextBlock->size;
					
					if (nextBlock == freemem) {
						freemem = currentBlock;
						prevcurrentblock->next = currentBlock->next;
						if (nextBlock->next != currentBlock) {
							currentBlock->next = nextBlock->next;
						}
					} else {
						prevNextBlock->next = nextBlock->next;
						
					}
				}
			}
			prevNextBlock = nextBlock;
			nextBlock = nextBlock->next;
		}
		if (currentBlock->size == size) {
			prevcurrentblock = currentBlock;
			currentBlock = currentBlock->next;
		}
	}
}

void cm_defrag20(void) {
	memblock *currentBlock = (memblock *)mempool;
	memblock *nextBlock = (memblock *)((char *)(currentBlock + 1) + currentBlock->size);
	memblock *listend = NULL;
	
	if(freemem) {		
		while (currentBlock && (char *)nextBlock < mempool + MEM_POOL_SIZE) {
			if (currentBlock->next != (memblock *)MAGIC_INT) {
				if (nextBlock->next != (memblock *)MAGIC_INT) {
					currentBlock->size += sizeof(memblock) + nextBlock->size;
				} else {
					currentBlock = nextBlock;
				}
			} else {
				currentBlock = nextBlock;			
			}
			nextBlock = (memblock *)((char *)(currentBlock + 1) + currentBlock->size);
		}
		
		memblock *currentBlock = (memblock *)mempool;
		while (currentBlock && (char *)currentBlock < mempool + MEM_POOL_SIZE) {
			if (currentBlock->next != (memblock *)MAGIC_INT) {
				if (listend) {
					listend->next = currentBlock;
					listend = listend->next;
					listend->next = NULL;
				} else {
					freemem = currentBlock;
					freemem->next = NULL;
					listend = freemem;
				}
			}
			currentBlock = (memblock *)((char *)(currentBlock + 1) + currentBlock->size);
		}
	}
}

/*
 * Wenn n größer als dest ist, dann gibt es einen Fehler
 * Wenn n größer als src ist, dann gibt es einen Fehler :)
 * wenn src und dest identisch sind, dann wird unnötig kopiert
 */
void *cm_memcpy(void *dest, const void *src, size_t n) {
	if (!dest || !src || ((int)((memblock *)dest-1)->next) != MAGIC_INT 
			|| ((int)((memblock *)src-1)->next) != MAGIC_INT ||
			(char *) src < mempool || (char *) src > mempool + MEM_POOL_SIZE ||
			(char *) dest < mempool || (char *) dest > mempool + MEM_POOL_SIZE) {
		return dest;
	}
	for (int i = 0; i < n; i++) {
		*((char *)dest + i) = *((char *)src + i);
	}
	return dest;
}

void *cm_realloc(void *ptr, size_t size) {
	if (!ptr) {
		return cm_malloc(size);
	}
	if(((int)((memblock *)ptr-1)->next) == MAGIC_INT) {
		if (ptr && size == 0) {
			cm_free(ptr);
			return NULL;
		}
		if (ptr && size > 0) {
			if (((memblock *)ptr-1)->size == size) {
				return ptr;
			}
			void *mew = cm_malloc(size);
			if (mew) {
				mew = cm_memcpy(mew,ptr,size);
				cm_free(ptr);
				return mew;
			}
			return NULL;
		}
	}
	return ptr;
}
