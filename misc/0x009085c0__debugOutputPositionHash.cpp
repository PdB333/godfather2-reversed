// FUNC_NAME: debugOutputPositionHash
void __cdecl debugOutputPositionHash(void* context, int someParam)
{
    // Get manager object that holds position data
    int manager = FUN_00471610();  // Likely returns pointer to object like PlayerPositionManager or GodfatherGameManager
    // Read the position floats from manager +0x30, +0x34, +0x38 (X, Y, Z)
    float posX = *(float*)(manager + 0x30);
    float posY = *(float*)(manager + 0x34);
    float posZ = *(float*)(manager + 0x38);

    // Build a 12-hex-digit string from the lower 16 bits of each integer part
    char debugStr[16];
    __snprintf(debugStr, 0x10, "%04X%04X%04X",
               (int)posX & 0xffff,
               (int)posY & 0xffff,
               (int)posZ & 0xffff);
    debugStr[15] = 0;  // Ensure null termination (redundant, snprintf already guarantees it)

    // Call a UI debug output function via a global vtable pointer
    // DAT_012234e0 is a global pointer to an object with a vtable; offset 0x14 is a method
    // The method takes (context, someParam, debugStr)
    void (*uiOutputFunc)(void*, int, char*) = (void (*)(void*, int, char*))(*(int*)DAT_012234e0 + 0x14);
    uiOutputFunc(context, someParam, debugStr);
}