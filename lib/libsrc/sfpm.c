#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
//This function is the opposite of the lock function. It takes the output of lock as input.
int unlock(struct lfs ls){
    ls.l.l_type = F_UNLCK;
    if (fcntl(ls.fd, F_SETLK, &(ls.l))==-1){
        printf("[unlock] [strerror] %s\n",strerror(errno));
        return -1;
    }
    close(ls.fd);
    return 1;
}
//This function uses read() to read from the socket. It doesn't tamper with recv's output. It adds a null terminator though. buf_size is used as array size, no extra bytes for null terminator are allocated.
void package_code(char *ip, int port,char *code,uint32_t buf_size){
    int sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in s;
    bzero(&s,sizeof(struct sockaddr_in));
    if(sock<0){
        printf("[package_code] [strerror] %s\n",strerror(errno));
        return;
    }
    char buffer[buf_size];
    if(buffer==NULL){
        printf("[package_code] [strerror] %s\n",strerror(errno));
        return;
    }
    s.sin_addr.s_addr=inet_addr(ip);
    s.sin_family=AF_INET;
    s.sin_port=port;
    if (connect(sock,(struct sockaddr*)&s,sizeof(struct sockaddr_in))<0){
        printf("[package_code] [strerror] %s\n",strerror(errno));
        return;
    }
    if(send(sock,code,strlen(code),0)==-1){
        printf("[package_code] [strerror] %s\n",strerror(errno));
        return;
    }
    int r;
    if((r=recv(sock,buffer,buf_size,0))==-1){
        printf("[package_code] [strerror] %s\n",strerror(errno));
        return;
    }
    close(sock);
    buffer[r+1]='\0';
    printf("%s\n",buffer);
}