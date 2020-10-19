
#define PY_SSIZE_T_CLEAN
#include <Python.h>

int 	main(int argc, char *argv[])
{
	FILE 	*fd;
	wchar_t	*program;

	program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL)
    {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }	
	Py_SetProgramName(program);
	Py_Initialize();
	PyRun_SimpleFile(fd, argv[1]);
	Py_Finalize();
	return 0;
}