LARGE_INTEGER FUN_00402270()
{
    LARGE_INTEGER counter;

    QueryPerformanceCounter(&counter);
    return (LARGE_INTEGER)counter.QuadPart;
}