#include "iostream.h"
#include "String.h"

using namespace std;

int main(int argc, char* argv[])
{
	string* msg = new string("Hello world");
	cout << *msg << endl;
	delete msg;
	// printf("hello world");;
	return 0;
}