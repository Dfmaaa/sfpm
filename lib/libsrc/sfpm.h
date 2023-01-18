#include <fcntl.h>
#include <unistd.h>
struct lfs{
    int fd;
    struct flock l;
};
struct lfs lock(char *);
int unlock(struct lfs);
