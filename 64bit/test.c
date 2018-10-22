#include "minicrt.h"

int main(int argc, char* argv[])
{
	int i;
	FILE* fp;
	int len;
	
	char** v = malloc(argc * sizeof(char*));
	for(i=1; i<argc; i++) {
		v[i] = malloc(strlen(argv[i]) + 1);
		strcpy(v[i], argv[i]);
		len = strlen(v[i]);
		printf("%d %s\n", len, v[i]);
	}
	
	fp = fopen("test.txt", "w");
	for(i=1; i<argc; ++i) {
		int len = strlen(v[i]);
		fwrite(&len, 1, sizeof(int), fp);
		fwrite(v[i], 1, len, fp);
	}
	fclose(fp);

	fp = fopen("test.txt", "r");
	for(i=1; i<argc; ++i) {
		int len = strlen(v[i]);
		char* buf;
		fread(&len, 1, sizeof(int), fp);
		buf = malloc(len + 1);
		fread(buf, 1, len, fp);
		buf[len] = '\0';
		printf("%d %s\n", len, buf);
		free(buf);
		free(v[i]);
	}
	fclose(fp);

	return 1;
}
