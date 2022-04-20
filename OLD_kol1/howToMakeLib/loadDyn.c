#include <dlfcn.h>
int main()
{
    void *handle = dlopen("libmy_library.so", RTLD_LAZY);
    if (!handle)
    { /*error*/
    }

    void (*lib_fun)();
    lib_fun = (void (*)())dlsym(handle, "my_library_function");

    if (dlerror() != NULL)
    { /*error*/
    }

    (*lib_fun)();

    dlclose(handle);
}