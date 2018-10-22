#include "minicrt.h"
#include "iostream.h"
#include "String.h"
#ifdef WIN32
#include <Windows.h>
#endif

namespace std {

	stdout_stream::stdout_stream() : ofstream()
	{
		fp = stdout;
	}

	stdout_stream cout;

	ofstream::ofstream() : fp(0) {}

	ofstream::ofstream(const char* filename, ofstream::openmode md) : fp(0)
	{
		open(filename, md);
	}

	ofstream::~ofstream()
	{
		close();
	}

	ofstream& ofstream::operator<<(char c)
	{
		fputc(c, fp);
		return *this;
	}

	ofstream& ofstream::operator<<(int n)
	{
		// fprintf(fp, "%d", n);
		char buf[16];
		itoa(n, buf, 10);
		fputc(buf, fp);
		return *this;
	}

	ofstream& ofstream::operator<<(const char* str)
	{
		// fprintf(fp, "%s", str);
		fputs(str, fp);
		return *this;
	}

	ofstream& ofstream::operator<<(ofstream& (*mainip)(ofstream&))
	{
		return mainip(*this);
	}


	void ofstream::open(const char* filename, ofstream::openmode md =
		ofstream::out)
	{
		char mode[4];
		close();
		switch (md)
		{
			case out | trunc:
				strcpy(mode, "w");
				break;
			case out | in | trunc:
				strcpy(mode, "w+");
				break;
			case out | trunc | binary:
				strcpy(mode, "wb");
				break;
			case out | in | trunc | binary:
				strcpy(mode, "wb+");
		}
		fp = fopen(filename, mode);
	}

	void ofstream::close()
	{
		if (fp)
		{
			fclose(fp);
			fp = 0;
		}
	}

	ofstream& ofstream::write(const char* buf, unsigned size)
	{
		fwrite(buf, 1, size, fp);
		return *this;
	}
}