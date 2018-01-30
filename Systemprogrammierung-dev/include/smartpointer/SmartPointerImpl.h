#ifndef SMARTPOINTERIMPL_H
#define SMARTPOINTERIMPL_H

#include "smartpointer/SmartPointer.h"
#include "smartpointer/NullPointerException.h"
#include <string>
#include <iostream>

using namespace std;

template<class T>
SmartPointer<T>::SmartPointer(T * const p) 
: pObj(p) {
	if (pObj) {
		rc = new RefCounter(); 
		rc->inc(); 
	} else {
		rc = nullptr;
	}
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& sp) 
: pObj(sp.pObj), rc(sp.rc) {
	if (rc) {
		rc->inc();
	} 
}

template<class T>
SmartPointer<T>::~SmartPointer() { deleteObject(); }

template<class T>
T *SmartPointer<T>::operator->() const { 
	if(pObj) {
		return pObj;
	} 
	throw NullPointerException();
 }

template<class T>
T &SmartPointer<T>::operator*() const {
	if(pObj) {
		return *pObj;
	} 
	throw NullPointerException();
}

template<class T>
const T *SmartPointer<T>::getObject() const { return pObj; }

template<class T>
const RefCounter *SmartPointer<T>::getRefCounter() const { return rc; }

template<class T>
const SmartPointer<T> &SmartPointer<T>::operator=(T * const p) {
	if (pObj != p) { 
		deleteObject();
		pObj = p;
		if (p) {
			rc = new RefCounter(); 
			rc->inc();
		} else {
			rc = nullptr;
		} 
	}	
	return *this; 
}

template<class T>
const SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T>& p) {
	if (this != &p) {
		deleteObject();
		pObj = p.pObj; 
		rc = p.rc;
		if (rc) {
			rc->inc();
		} 
	}
	return *this; 
}

template<class T>
bool SmartPointer<T>::operator==(const SmartPointer<T>& p) const { return pObj == p.pObj; }

template<class T>
bool SmartPointer<T>::operator!=(const SmartPointer<T>& p) const { return pObj != p.pObj; }

template<class T>
SmartPointer<T>::operator bool() const { return pObj != nullptr; }

template<class T>
void SmartPointer<T>::deleteObject() { 
	if (rc) {
		rc->dec(); 
		if (rc->isZero()) { 
			delete rc; 
			delete pObj; 
		} 
	}
}

#endif
