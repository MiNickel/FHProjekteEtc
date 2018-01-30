define printFree
	set $arg = freemem
	while($arg != NULL)
		showInfo $arg
		set $arg = $arg->next
	end
end

define printBlock
	set $mem = (memblock *)$arg0
	set $mem--
	if($mem->next == MAGIC_INT)
		showInfo $mem
		set $content = (char *)$arg0
		set $counter = $mem->size
		while ($counter > 0)
			print $content
			set $content++
			set $counter--
		end
	end
end

define printAll
	set $arg = (memblock *)mempool
	while ($arg < mempool + MEM_POOL_SIZE)
		showInfo $arg
		set $arg = (memblock *)((char *)($arg + 1) + $arg->size)
	end
end

define showInfo
	print $arg0
	print $arg0->size
	print $arg0->next
end