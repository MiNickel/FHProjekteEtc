#include <exception>

#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

class NullPointerException: public std::exception {
	public:
		const char* what() const throw() {
			return "You tried to access an object that was null!";
		}
};
#endif
