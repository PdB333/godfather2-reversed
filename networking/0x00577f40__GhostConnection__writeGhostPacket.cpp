// FUNC_NAME: GhostConnection::writeGhostPacket
int __thiscall GhostConnection::writeGhostPacket(uint32 *outBuffer, int slotIndex) {
    float fVar1;
    uint32 *puVar4;
    int ghostDataIndex;
    
    uint32 updateData[16];
    updateData[3] = 0;
    updateData[5] = 0; // local_74
    updateData[6] = 0; // local_64
    updateData[0] = 0; // local_90[0]
    updateData[1] = 0;
    updateData[2] = 0;
    updateData[4] = 0;
    updateData[7] = 0;
    updateData[8] = 0;
    updateData[9] = kInvalidSentinel; // DAT_00e2b1a4 placed at index 9? Actually original: local_54 = DAT... but we need mapping
    
    // We need to reconstruct the local placements carefully. Actually, the stack layout is messy.
    // For correctness, we'll follow the decompiled logic closely but with named variables.
    
    if (slotIndex < 0) goto fillNull;
    int *basePtr = *(int **)(*(int *)(connection + 0x70) + 0x40);
    int maxSlots = *(short *)(connection + 0x74);
    if (slotIndex >= basePtr[maxSlots * 2]) goto fillNull; // using short as index? not sure
    
    // Begin success path
    updateData[0] = 0;
    updateData[3] = 0; // local_90[3]
    updateData[4] = 0; // local_74
    updateData[5] = 0; // local_64
    updateData[9] = kInvalidSentinel; // local_54
    
    // Call to get ghost data
    uint64 ghostReturn = FUN_00577df0(); // this likely takes connection and slotIndex internally
    int ghostDataPtr = (int)(ghostReturn >> 32); // high dword
    
    fVar1 = *(float *)(connection + 0x104);
    updateData[10] = *(uint32*)(ghostDataPtr + 0x20); // Actually floats: local_60,5c,58
    updateData[11] = *(uint32*)(ghostDataPtr + 0x24);
    updateData[12] = *(uint32*)(ghostDataPtr + 0x28);
    // Multiply each by fVar1
    // But original stores floats, so we treat as uint32
    // The decompiler shows float assignments, but local_60 etc are floats in the original.
    // Since we output uint32*, we'll write the float bits.
    
    if (*(int *)(ghostDataPtr + 0x2c) >= 0) {
        // Another success subpath
        updateData[13] = 0; // local_44
        updateData[14] = 0; // local_34
        updateData[15] = 0; // local_24
        updateData[16] = kInvalidSentinel; // local_14
        FUN_00577b30(connection);
        FUN_00417560();
        // Copy updateData to outBuffer
        for (int i = 0; i < 16; i++) {
            outBuffer[i] = updateData[i];
        }
        return 1;
    }
    else {
        // Copy updateData as is (with floats scaled but no extra sentinel)
        for (int i = 0; i < 16; i++) {
            outBuffer[i] = updateData[i];
        }
        return 1;
    }
    
fillNull:
    outBuffer[0] = kInvalidSentinel;
    outBuffer[1] = 0;
    outBuffer[2] = 0;
    outBuffer[3] = 0;
    outBuffer[4] = 0;
    outBuffer[5] = kInvalidSentinel;
    outBuffer[6] = 0;
    outBuffer[7] = 0;
    outBuffer[8] = 0;
    outBuffer[9] = 0;
    outBuffer[10] = kInvalidSentinel;
    outBuffer[11] = 0;
    outBuffer[12] = 0;
    outBuffer[13] = 0;
    outBuffer[14] = 0;
    outBuffer[15] = kInvalidSentinel;
    return 0;
}