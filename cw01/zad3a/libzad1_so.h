#ifndef __LIBZAD1_H__
#define __libzad1_h__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct WCMem{
    char** data;
    size_t maxsize;
    size_t size;
} WCMem;

WCMem (*create_struct)(size_t size);
void (*init_struct)(WCMem*, size_t );
char* (*get_from_struct)(WCMem*,size_t );
void (*pop_from_struct)(WCMem*,size_t );
void (*push_to_struct)(WCMem* ,char* );
void (*clear_struct)(WCMem*);
void (*destroy_struct)(WCMem*);
#endif