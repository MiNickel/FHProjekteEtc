#include "smartpointer/RefCounter.h"

RefCounter::RefCounter() : n(0) { }

void RefCounter::inc() { n++; }
void RefCounter::dec() { if (n > 0) n--; }
bool RefCounter::isZero() const { return n == 0; }
unsigned int RefCounter::getRefCount() const { return n; }
