#include "String.h"
#include "iostream.h"

namespace std {
	string::string(const char* str):
		len(0), pbuf(0)
	{
		*this = str;
	}

	string::string(const string& s):
		len(0), pbuf(0)
	{
		*this = s;
	}

	string::~string()
	{
		if(pbuf != 0) {
			delete[] pbuf;
			pbuf = 0;
		}
	}

	string& string::operator=(const string& s)
	{
		if (&s == this)
			return *this;
		this->~string();
		len = s.len;
		pbuf = strcpy(new char[len+1], s.pbuf);
		return *this;
	}

	string& string::operator=(const char*s)
	{
		this->~string();
		len = strlen(s);
		pbuf = strcpy(new char[len+1], s);
		return *this;
	}

	const char& string::operator[](unsigned idx) const
	{
		return pbuf[idx];
	}

	char& string::operator[](unsigned idx)
	{
		return pbuf[idx];
	}

	const char* string::c_str() const
	{
		return pbuf;
	}
	
	unsigned string::length() const
	{
		return len;
	}

	unsigned string::size() const
	{
		return len;
	}

	ofstream& operator<<(ofstream& o, const string& s)
	{
		o << s.c_str();
	}
}