// FUNC_NAME: getGlobalDouble
// Address: 0x005c7630
// Role: Reads a global double-precision floating-point value from a static location.
// The decompiled output suggests an x87 extended-precision float (float10), but double is typical in modern engines.
// The caller (0x00945a20) likely uses this as a global parameter (e.g., time scale, multiplier).

extern double gGlobalDouble;  // Defined at 0x0119d0bc

double getGlobalDouble(void) {
    return gGlobalDouble;
}