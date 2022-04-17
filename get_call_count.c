// #include <stdio.h>
#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int main()
{

    write(0, "first\n", 6);
    write(0, "second\n", 7);

    int a = get_call_count(SYS_fork);
    
    printf(1, "a: %d\n", a);

    exit();
}