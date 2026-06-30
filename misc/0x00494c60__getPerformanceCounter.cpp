// FUNC_NAME: getPerformanceCounter
LARGE_INTEGER getPerformanceCounter(void)
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter;
}