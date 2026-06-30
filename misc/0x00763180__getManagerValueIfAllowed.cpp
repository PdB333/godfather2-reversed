// FUNC_NAME: getManagerValueIfAllowed
// Function at 0x00763180
int getManagerValueIfAllowed(int isAllowed) {
    if (isAllowed != 0) {
        return getManagerValue(gManagerPointer); // Calls function at 0x0043b870 with global data at 0x01131074
    }
    return 0;
}