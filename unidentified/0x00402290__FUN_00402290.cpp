#include <windows.h>

LARGE_INTEGER FUN_00402290()
{
    LARGE_INTEGER local_c;

    QueryPerformanceCounter(&local_c);
    return (LARGE_INTEGER)local_c.QuadPart;
}