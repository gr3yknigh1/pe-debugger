#include <stdio.h>

#include <windows.h>

int
main(void)
{

    puts("Hi hi there!");

    OutputDebugStringA("DebugString");

    int x = 1, y = 2;

    int z = x + y;

    printf("z = (%d)\n", z);

    getchar();
    return 0;
}
