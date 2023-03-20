#ifndef __LIBZAD1_H__
#define __LIBZAD1_H__

#include <stdlib.h>

typedef struct WCMem{
    char** data;
    size_t maxsize;
    size_t size;
} WCMem;

WCMem create_struct(size_t size);
void init_struct(WCMem *struc, size_t size);
char* get_from_struct(WCMem *struc,size_t index);
void pop_from_struct(WCMem *struc,size_t index);
void push_to_struct(WCMem* struc,char* filename);
void clear_struct(WCMem *struc);

#endif