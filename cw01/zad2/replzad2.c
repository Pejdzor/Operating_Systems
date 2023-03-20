#ifdef USE_DLL
    #include "libzad1_so.h"
#else
    #include "libzad1.h"
#endif

#include "dllmanager.h"
#include <time.h>
#include <sys/times.h>
int running=1;
typedef enum{INIT,COUNT,SHOW,DELETE,DESTROY,QUIT,INVALID} command_id;
char* commands[]={"init", "count", "show", "delete", "destroy","quit"};
WCMem data;
int is_initialized=0;

command_id get_command(const char* line){
    if (strncmp(line,commands[0],4)==0){
        return INIT;
    }else if(strncmp(line,commands[2],4)==0){
        return SHOW;
    }else if(strncmp(line,commands[5],4)==0){
        return QUIT;
    }else if(strncmp(line,commands[1],5)==0){
        return COUNT;
    }else if(strncmp(line,commands[3],6)==0){
        return DELETE;
    }else if(strncmp(line,commands[4],7)==0){
        return DESTROY;
    }else {
        return INVALID;
    }
}

void execute_command(command_id comm, char* line){
    if (is_initialized==0 && comm!=INIT && comm!=QUIT){
        printf("[LIB TEST]>> You must initialize structure first!\n");
        return;
    }else if(is_initialized==1 && comm==INIT){
        printf("[LIB TEST]>> Structure is already initialized!\n");
        return;
    }else if (is_initialized==0 && comm==DESTROY){
        printf("[LIB TEST]>> You can't destroy uninitialized structure!\n");
        return;
    }
    size_t number;
    char* path=malloc(sizeof(char*));
    switch(comm){
        case INIT:
            sscanf(line,"init %zu",&number);
            init_struct(&data,number);
            is_initialized=1;
            return;
        case COUNT:
            line+=strlen("count ");
            number=strcspn(line,"\n");
            strncpy(path,line,number);
            push_to_struct(&data,path);
            return;
        case SHOW:
            sscanf(line,"show %zu",&number);
            get_from_struct(&data,number);
            return;
        case DELETE:
            sscanf(line,"delete %zu",&number);
            pop_from_struct(&data,number);
            return;
        case DESTROY:
            destroy_struct(&data);
            is_initialized=0;
            return;
        case QUIT:
            running=0;
            destroy_struct(&data);
            return;
        case INVALID:
            printf("%s","[LIB TEST]>> 'init [size] - initialize structure\n");
            printf("%s","[LIB TEST]>> 'show [index] - show value at [index] position\n");
            printf("%s","[LIB TEST]>> 'count [filepath] - counts words, lines and character from given file\n");
            printf("%s","[LIB TEST]>> 'delete [index] - deletes data from [index] position in the structure\n");
            printf("%s","[LIB TEST]>> 'destroy - clears whole structure\n");
            printf("%s","[LIB TEST]>> 'quit - quit program\n");
            return;
    }

}

int main(){
    get_dll_functions("libwc.so");
 command_id commandId;

 struct tms tms_time_start, tms_time_end;
 struct timespec timespec_time_start, timespec_time_end;
    while (running==1){
        printf("%s","[LIB TEST]>> ");
        char* komenda=malloc(1024*sizeof(char));
        fgets(komenda,1024,stdin);
        fflush(NULL);
        commandId=get_command(komenda);
        fflush(NULL);

        clock_gettime(CLOCK_REALTIME,&timespec_time_start);
        times(&tms_time_start);
        execute_command(commandId,komenda);
        clock_gettime(CLOCK_REALTIME,&timespec_time_end);
        times(&tms_time_end);

        puts("TIME TAKEN:");
        printf("REAL: %ldns\n",timespec_time_end.tv_nsec-timespec_time_start.tv_nsec);
        printf("USER: %ldticks\n", tms_time_end.tms_cutime-tms_time_start.tms_cutime);
        printf("SYSTEM: %ldticks\n", tms_time_end.tms_cstime-tms_time_start.tms_cstime);
        fflush(NULL);
        free(komenda);
    }

    return 0;
}