#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int n = 0;
    if (argc >= 2) n = atoi(argv[1]);

    printf("Get sysinfo from kernel %d\n", n);
    printf("%d\n", sysinfo(n));

    exit(0);
}