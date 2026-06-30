// FUNC_NAME: getGlobalSimTime
// Address: 0x0054eb00
// Retrieves the global simulation time value (extended precision float, stored as double).
double getGlobalSimTime(void)
{
    // DAT_00e2cb90 is the global float variable (likely double precision)
    return (double) *((double*)0x00e2cb90);  // Cast to double for compatibility
}