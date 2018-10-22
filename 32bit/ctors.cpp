typedef void (*init_func)(void);

#ifdef WIN32

#else

void run_hooks();
extern "C" void do_global_ctors()
{
	run_hooks();
}
#endif