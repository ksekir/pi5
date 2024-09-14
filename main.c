#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVNAME "/dev/gomel"

int main(){
    int fdev = open(DEVNAME, O_RDONLY);
    if (fdev == -1) {
        printf("failed to open %s\n", DEVNAME);
        return -1;
    }
    printf("Open %s\n", DEVNAME);
    close(fdev);
    return 0;
} 
