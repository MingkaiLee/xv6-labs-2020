#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *root, char *aim) {

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "usage: find [find directory] file");
        exit(1);
    }

    if (argc == 2) {
        find("/", argv[1]);
    } else {
        find(argv[1], argv[2]);
    }
}