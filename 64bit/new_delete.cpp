extern "C" void* malloc(unsigned long);
extern "C" void free(void*);

void* operator new(unsigned long size)
{
	return malloc(size);
}

void operator delete(void* p, unsigned long size)
{
	free(p);
}

void* operator new[](unsigned long size)
{
	return malloc(size);
}

void operator delete[](void* p)
{
	free(p);
}
