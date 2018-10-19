#ifndef __STRING__
#define __STRING__

namespace std {

	class string
	{
		unsigned len;
		char* pbuf;

	public:
		explicit string(const char* str);
		string(const string&);
		~string();
		string& operator=(const string&);
		string& operator=(const char* s);
		const char& operator[](unsigned idx) const;
		char& operator[](unsigned idx);
		const char* c_str() const;
		unsigned length() const;
		unsigned size() const;
	};
}

#endif