// FUNC_NAME: NetConnection::processIncomingPacket
void NetConnection::processIncomingPacket(void)
{
    int status;
    int *thisPtr; // unaff_EDI
    int bytesRead; // local_554
    undefined2 packetHeaderField1; // local_550
    undefined2 packetHeaderField2; // local_54e
    u_long networkZero; // local_54c
    undefined4 unknown1; // local_548
    undefined4 unknown2; // local_544
    undefined4 unknown3; // local_540
    void **functionTable; // local_53c
    undefined4 unknown4; // local_538
    undefined4 unknown5; // local_534
    char *buffer; // local_530
    int bufferSize; // local_52c
    char isAllocated; // local_528
    undefined4 flags; // local_524
    undefined1 flag1; // local_520
    undefined1 flag2; // local_51f
    int maxSize; // local_510
    undefined4 maxSize2; // local_50c
    undefined1 flag3; // local_504
    undefined1 bufferData[1028]; // local_404

    // Increment reentrancy guard
    g_reentrancyCounter++;

    // Initialize local variables
    buffer = bufferData;
    unknown4 = 0;
    unknown5 = 0;
    bufferSize = 0x400;
    isAllocated = '\0';
    maxSize = 0x2000;
    maxSize2 = 0x2000;
    flags = 0;
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    unknown1 = 0;
    unknown2 = 0;
    unknown3 = 0;
    functionTable = &g_packetHandlerTable; // PTR_LAB_00e42f38
    packetHeaderField1 = 0;
    packetHeaderField2 = 0;
    networkZero = htonl(0);

    // Store some value from another function into this+0x64 (offset 0x19*4)
    thisPtr[0x19] = FUN_0065c190();

    // Main processing loop
    while (true) {
        status = FUN_00658390(&packetHeaderField1, bufferData, &bytesRead);
        if (isAllocated != '\0') {
            isAllocated = '\0';
            free(buffer);
        }
        bufferSize = bytesRead;
        maxSize = bytesRead * 8;
        buffer = bufferData;
        maxSize2 = 0;
        flags = 0;
        flag1 = 0;
        flag2 = 0;
        flag3 = 0;
        unknown1 = 0;
        unknown2 = 0;
        unknown3 = 0;
        if (status != 0) break;
        // Call virtual method at vtable+0xc (likely handlePacket)
        (this->vtable[0xc])(&packetHeaderField1, &functionTable);
    }

    // Decrement reentrancy guard
    g_reentrancyCounter--;
    FUN_0064b440(); // Likely cleanup or unlock
    return;
}