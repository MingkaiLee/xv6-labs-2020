#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *getPureName(char *path) {
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    return p;
}

void find(char *path, const char *aim) {
    char buf[512], *p;
    int fd, l;
    struct dirent de;
    struct stat st;

    if (stat(path, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        return;
    }

    // print when names match
    if (strcmp(aim, getPureName(path)) == 0) printf("%s\n", path);

    if (st.type == T_DIR) {
        if ((fd = open(path, 0)) < 0) {
            fprintf(2, "find: cannot open %s\n", path);
            return;
        }
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("ls: path too long\n");
        }
        strcpy(buf, path);
        l = strlen(buf);
        buf[l++] = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if ((strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0) || (de.inum == 0)) continue;
            p = buf + l;
            memmove(p, de.name, strlen(de.name));
            p[strlen(de.name)] = 0;
            find(buf, aim);
        }
        close(fd);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "usage: find [find directory] file");
        exit(1);
    }

    if (argc == 2) {
        find(".", argv[1]);
    } else {
        find(argv[1], argv[2]);
    }
    exit(0);
}