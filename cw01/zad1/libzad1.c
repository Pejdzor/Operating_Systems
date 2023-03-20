#include <stdio.h>
#include "libzad1.h"
#include <string.h>

WCMem  create_struct(size_t size){
    return (WCMem){.data=calloc(size,sizeof(char*)),
                   .maxsize=size,
                   .size=0};
}

void init_struct(WCMem *struc,size_t size){
    struc->data=calloc(size, sizeof(char*));
    struc->maxsize=size;
    struc->size=0;
}

char* get_from_struct(WCMem *struc,size_t index){
    if (struc->size<=index){
        return "INDEX OUT OF RANGE";
    }
    return struc->data[index];
}

void pop_from_struct(WCMem *struc,size_t index){
    if (index>=struc->size){
        printf("%s","There's nothing to pop!");
    }else{
        for (int i=index;i<struc->size-1;i++){
            struc->data[i]=struc->data[i+1];
        }
        free(struc->data[struc->size-1]);
    }
}

long file_size(FILE* file){
    fseek(file,0,SEEK_END);
    long size=ftell(file);
    fseek(file,0,SEEK_SET);
    return size;
}

char* read_file_content(char* filename){
    FILE* fhandler=fopen(filename,"r");
    size_t size=file_size(fhandler);
    char* tmp=calloc(size,sizeof(char));
    fread(tmp,sizeof(char),size,fhandler);
    fclose(fhandler);
    return tmp;
}


void push_to_struct(WCMem* struc,char* filename){

    char tmp_fname[]="/tmp/zad1tmp_XXXXXX";
    int tmpfile=mkstemp(tmp_fname);

    if (tmpfile==0){
        printf("Failed to create a temporary file");
        return;
    }

    char command[2048];
    snprintf(command,2048,"wc '%s' 1> '%s'",filename,tmp_fname);
    system(command);
    char *buffer=read_file_content(tmp_fname);
    if (strlen(buffer)==0) {
        printf("%s", "Failed to read temporary file");
    }
    snprintf(command,2048,"rm -f '%s' 2> /dev/null",tmp_fname);
    system(command);

    if (struc->size<struc->maxsize){
        struc->data[struc->size]=buffer;
        (struc->size)++;
    }else{
        printf("%s","No space in the struct");
    }

}

void clear_struct(WCMem *struc){
    for (size_t i=0;i<struc->size;i++){
        free(struc->data[i]);
    }
    struc->size=0;
}