#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int fd_read) {
    int buf[1];
    int len = read(fd_read, buf, 1);
    int p = buf[0];
    printf("prime %d\n", p);
    //  to check if created subprocess
    int apply_send = 0;
    // pipe
    int pp[2];
    while (len > 0) {
        len = read(fd_read, buf, 1);
        if (len > 0) {
            int n = buf[0];
            if ((n % p) > 0) {
                if (!apply_send) {
                    pipe(pp);
                    apply_send = 1;
                    if (fork() == 0) {
                        close(pp[1]);
                        prime(pp[0]);
                    } else {
                        close(pp[0]);
                    }
                }
                write(pp[1], buf, 1);
            }
        }
    }
    // check if created subprocess
    close(fd_read);
    if (apply_send) {
        int child_status;
        close(pp[1]);
        wait(&child_status);
    }
    // exit
    exit(0);
}

int main(int argc, char *argv[]) {
    int buf[1];
    int pp[2];
    pipe(pp);
    if (fork() == 0) {
        close(pp[1]);
        prime(pp[0]);
    } else {
        close(pp[0]);
        int child_status;
        for (int i = 2; i <= 35; i++) {
            buf[0] = i;
            write(pp[1], buf, 1);
        }
        close(pp[1]);
        wait(&child_status);
    }
    exit(0);
}
