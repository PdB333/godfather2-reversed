// FUNC_NAME: callGlobalMethod
// Address: 0x005e6550
// Role: Thin wrapper that forwards a parameter to a function on a global object (DAT_012234bc).

void callGlobalMethod(int param) {
    // Calls FUN_005e49d0 with the global handle and the provided parameter.
    FUN_005e49d0(DAT_012234bc, param);
}