#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p_p_send[2];
    int p_c_send[2];
    char msg[1] = {'a'};
    char buf[1];
    pipe(p_p_send);
    pipe(p_c_send);
    if (fork() == 0) {
        read(p_p_send[0], buf, 1);
        int pid = getpid();
        printf("%d: received ping\n", pid);
        write(p_c_send[1], msg, 1);
        close(p_c_send[1]);
    } else {
        write(p_p_send[1], msg, 1);
        close(p_p_send[1]);
        read(p_c_send[0], buf, 1);
        int pid = getpid();
        printf("%d: received pong\n", pid);
    }
    exit(0);
}