#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "structs.h"
#include "sfpm.h"

//This function returns the pointer to a structure which contains fd and lock
struct lfs lock(char *fname){
    int f;
    struct flock l;
    struct lfs ls;
    if((f=open(fname,O_RDONLY))==-1){
        return ls;
    }
    l.l_type = F_RDLCK;
    l.l_start = 0;
    l.l_whence = SEEK_SET;
    l.l_len = 0;
    if (fcntl(f, F_SETLK, &lock) == -1) {
        printf("[lock] [strerror] %s\n",strerror(errno));
        close(f);
        return ls;
    }
    ls.fd=f;
    ls.l=l;
    return ls;
}

int unlock(struct lfs ls){
    ls.l.l_type = F_UNLCK;
    if (fcntl(ls.fd, F_SETLK, &(ls.l))==-1){
        printf("[unlock] [strerror] %s\n",strerror(errno));
        return -1;
    }
    close(ls.fd);
    return 1;
}