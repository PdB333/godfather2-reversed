// FUNC_NAME: EntityManager::getByteFlagAtOffset22
unsigned char EntityManager::getByteFlagAtOffset22(unsigned int index) {
    // local_5 and local_4 are output parameters for FUN_005f0560
    unsigned char byteOut;
    unsigned char arrayOut[4];
    
    // FUN_005f0560 performs a lookup based on index; returns pointer to an object or 0
    int objectPtr = FUN_005f0560(index, &byteOut, arrayOut);
    if (objectPtr != 0) {
        // Offset 0x22 is likely a status/flag byte in the found object
        return *(unsigned char*)(objectPtr + 0x22);
    }
    return 0;
}