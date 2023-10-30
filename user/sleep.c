#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc <= 1 || argc > 2) {
        fprintf(2, "usage: sleep pattern [seconds]\n");
        exit(1);
    }
    char *sleep_time = argv[1];
    int t = atoi(sleep_time);
    sleep(t);
    exit(0);
}