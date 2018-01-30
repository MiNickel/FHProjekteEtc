/*
 * Diese Header File wird fuer diverse Tests benoetigt.
 * NICHT VERAENDERN!
 */
#ifndef CMOCK_TEST_STUDI_H_
#define CMOCK_TEST_STUDI_H_

#include <cmock/cmock.h>

extern "C" {
#include "studiverwaltung/spfree.h" // use original function declaration
}

DECLARE_FUNCTION_MOCK1(FreeMock, sp_free, void(void*));

#endif /* CMOCK_TEST_FOO_MOCK_H_ */
