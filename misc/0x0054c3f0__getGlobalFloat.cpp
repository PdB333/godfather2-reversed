// FUNC_NAME: getGlobalFloat
// Function at 0x0054c3f0: Simple getter returning a float from a global variable (DAT_00e2cd54)
float getGlobalFloat() {
    extern float g_globalFloat; // DAT_00e2cd54
    return g_globalFloat;
}