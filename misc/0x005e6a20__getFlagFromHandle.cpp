// FUNC_NAME: getFlagFromHandle
char getFlagFromHandle(int handle) {
    int objectPtr;
    char outByte;
    char outBuffer[4];
    
    objectPtr = FUN_005f0560(handle, &outByte, outBuffer);
    if (objectPtr != 0) {
        // Return the byte at offset 0x22 from the found object
        return *(char *)(objectPtr + 0x22);
    }
    return 0;
}