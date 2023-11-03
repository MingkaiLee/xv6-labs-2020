#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int main(int argc, char *argv[]) {
    int idx, arg_idx, ptr, status;
    char *args[MAXARG];
    char buffer, *p;
    char arg[1024];
    if (argc > MAXARG) {
        fprintf(2, "xargs: argument count exceeds limit 32");
        exit(1);
    }
    for (idx = 1; idx < argc; idx++) {
        args[idx-1] = argv[idx];
    }
    ptr = argc - 1;
    arg_idx = 0;
    while (read(0, &buffer, 1) > 0) {
        switch (buffer)
        {
        case ' ':
            p = (char *)malloc(arg_idx * sizeof(char));
            for (idx = 0; idx < arg_idx; idx++) {
                p[idx] = arg[idx];
            }
            *(p+idx) = 0;
            args[ptr++] = p;
            // reset index
            arg_idx = 0;
            break;
        case '\n':
            p = (char *)malloc(arg_idx * sizeof(char));
            for (idx = 0; idx < arg_idx; idx++) {
                p[idx] = arg[idx];
            }
            *(p+idx) = 0;
            args[ptr++] = p;
            if (fork() == 0) {
                exec(argv[1], args);
                exit(0);
            } else {
                wait(&status);
            }
            // free the memory in heap
            for (idx = argc-1; idx < ptr; idx++) {
                free(args[idx]);
                args[idx] = 0;
            }
            // reset ptr and index
            arg_idx = 0;
            ptr = argc - 1;
            break;
        default:
            arg[arg_idx++] = buffer;
        }
    }
    
    exit(0);
}