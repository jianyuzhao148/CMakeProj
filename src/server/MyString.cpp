#include "MyString.h"
#include <string.h>

MyString::MyString(const char* str) {
	//this->str = str;//Ç³¿½±´
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}
MyString::MyString(const MyString& myString) {
	//this->str = str.str;//Ç³¿½±´
	this->str = new char[strlen(myString.str) + 1];
	strcpy(this->str, myString.str);
}

MyString& MyString::operator=(const MyString& myString) {
	if (&myString == this) {
		return *this;
	}
	delete[] this->str;
	this->str = new char[strlen(myString.str) + 1];
	strcpy(this->str, myString.str);
	return *this;
}

MyString::~MyString() {
	delete[] str;
}

char* MyString::GetCString()const {
	return this->str;
}