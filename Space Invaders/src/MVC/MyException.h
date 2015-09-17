/*
 * MyException.h
 *
 *  Created on: Nov 29, 2013
 *      Author: Armin Halilovic
 */

#include <exception>

/**
 * MyException to easily throw with a message.
 */
class MyException : public std::exception {
private:
	char* message;

public:
	/// Parametrized constructor.
	MyException(char* message) : message(message) { }

	/// Destructor.
	virtual ~MyException() throw() { }

	/// Return the exception's message.
	virtual const char* what() const throw() {
		return message;
	}
};
