#ifndef __DLLMANAGER_H__
#define __DLLMANAGER_H__

#ifdef USE_DLL
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
void get_dll_functions(const char* filepath){
    void *handle = dlopen(filepath,RTLD_LAZY);
    if (handle==NULL){
        printf("[DLL MANAGER] Failed to load DLL %s\n",filepath);
        return;
    }
    *(void **) (&init_struct) = dlsym(handle,"init_struct");
    *(void **) (&get_from_struct) = dlsym(handle,"get_from_struct");
    *(void **) (&pop_from_struct) = dlsym(handle,"pop_from_struct");
    *(void **) (&push_to_struct) = dlsym(handle,"push_to_struct");
    *(void **) (&clear_struct) = dlsym(handle,"clear_struct");
    *(void **) (&create_struct) = dlsym(handle,"create_struct");
    *(void **) (&destroy_struct) = dlsym(handle,"destroy_struct");
}
#else
void get_dll_functions(const char* filepath){}
#endif
#endif