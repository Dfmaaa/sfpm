#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
struct lfs{
    int fd;
    struct flock l;
};
struct lfs lock(char *);
int unlock(struct lfs);
void  package_code(char*,int,char*, uint32_t);