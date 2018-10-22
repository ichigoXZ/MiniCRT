#ifndef __IOSTREAM__
#define __IOSTREAM__

#include "minicrt.h"

namespace std {

	class ofstream
	{
	protected:
		FILE* fp;
		ofstream(const ofstream&);
	public:
		enum openmode{
			in=1, out=2, binary=4, trunc=8
		};
		ofstream();
		explicit ofstream(const char* filename,
			ofstream::openmode md = ofstream::out);
		~ofstream();
		ofstream& operator<<(char c);
		ofstream& operator<<(int n);
		ofstream& operator<<(const char* str);
		ofstream& operator<<(ofstream& (*)(ofstream&));
		void open(const char* filename, ofstream::openmode md =
			ofstream::out);
		void close();
		ofstream& write(const char* buf, unsigned size);
	};


	inline ofstream& endl(ofstream& o)
	{
		return o << '\n';
	}

	class stdout_stream : public ofstream {
	public:
		stdout_stream();
	};

	extern stdout_stream cout;
}

#endif