// FUNC_NAME: Connection::buildPacket

void Connection::buildPacket(void)
{
    int *piVar1;
    int *piVar2;
    undefined4 *puVar3;
    undefined4 *puVar4;
    char cVar5;
    uint uVar6;
    uint uVar7;
    int *thisPtr = unaff_EDI; // this pointer in EDI
    int *retAddrInfo = unaff_retaddr; // pointer to return address / connection info
    
    byte local_7b9 = 7;
    uint local_7b8;
    uint local_7b4;
    undefined **local_7b0 = &PTR_LAB_00e42f38; // global ghost data pointer
    undefined4 local_7ac = 0;
    undefined4 local_7a8 = 0;
    undefined1 *local_7a4 = local_678;
    undefined4 local_7a0 = 0x400;
    uint local_79c = local_79c & 0xffffff00;
    
    int local_798 = 0;
    byte local_794 = 0;
    byte local_793 = 0;
    undefined4 local_784 = 0x2000;
    undefined4 local_780 = 0x2000;
    undefined4 local_77c = 0;
    byte local_778 = 0;
    
    undefined1 local_678[1020]; // packet buffer
    undefined1 auStack_27c[4];
    undefined4 *puStack_278; // linked list of pending objects
    
    // — Begin packet header encoding —
    writeBits(8, &local_7b9); // packet type identifier (7)
    writeBits(0x40, (int)thisPtr + 0x133); // write 64 bits from member at +0x133 (likely a sequence or timestamp)
    
    uVar6 = (local_798 + 7) >> 3; // byte-align bit offset
    local_798 = uVar6 * 8;
    
    writeBits(0x40, (int)thisPtr + 0x13b); // write another 64 bits from +0x13b
    
    cVar5 = checkFlag(*(byte *)((int)thisPtr + 0x131)); // check flag at +0x131 (maybe pending ghost update?)
    if (cVar5 != '\0') {
        piVar2 = *(int **)(thisPtr[0x55] + 0x18); // thisPtr[0x55] is offset 0x154, deref +0x18 -> object
        if (piVar2 != (int *)0x0) {
            piVar2[2] = piVar2[2] + 1; // reference count increment
        }
        local_7b8 = piVar2[4]; // object size or number of bits
        if (local_7b8 < 0x400) {
            local_7b4 = local_7b8;
            writeBits(10, &local_7b4); // write size (10 bits)
            writeBits(local_7b8 * 8, piVar2[3]); // write object data (size*8 bits)
        }
        piVar1 = piVar2 + 2; // points to reference count
        *piVar1 = *piVar1 - 1;
        if (*piVar1 == 0) {
            // release ghost object
            (**(code **)(*piVar2 + 8))(); // virtual destructor at vtable+8
        }
        uVar7 = (local_798 + 7) >> 3;
        local_798 = uVar7 * 8;
        
        writeBits(0x80, (int)thisPtr + 0x162); // write 128 bits from +0x162 (maybe a mask or another object)
    }
    
    checkFlag((char)thisPtr[0x66]); // verify another flag at +0x66*4 = 0x198
    
    local_7b8 = thisPtr[0x29]; // read sequence number? +0x29*4 = 0xA4
    writeBits(0x20, &local_7b8); // write 32 bits (packet sequence)
    
    // Call virtual method at vtable offset 0x20: likely "writeGhostUpdates" or similar
    (**(code **)(*thisPtr + 0x20))(&local_7b0);
    
    // Process two linked lists of pending reliable objects (uVar7 and uVar6)
    if (uVar7 != 0) {
        processList(auStack_27c);
        addToContainer(uVar7, auStack_27c); // likely adds nodes to some container
        puVar4 = puStack_278;
        while (puVar4 != (undefined4 *)0x0) {
            puVar3 = (undefined4 *)puVar4[2]; // next pointer at +8
            *puVar4 = 0;
            puVar4[1] = 0;
            puVar4[2] = 0;
            puVar4 = puVar3;
        }
    }
    
    processList(auStack_27c);
    addToContainer(uVar6, auStack_27c);
    
    // Update packet counters
    thisPtr[0x67] = thisPtr[0x67] + 1; // outbound packet seq? +0x67*4 = 0x19C
    thisPtr[0x68] = *(int *)((int)retAddrInfo + 100); // +0x68*4 = 0x1A0 (possibly acked seq from caller)
    
    // Send the packet via lower layer
    sendPacket((int)retAddrInfo + 0x5c, auStack_67c, (local_79c + 7) >> 3, 0);
    
    // Clean up linked list
    while (puStack_278 != (undefined4 *)0x0) {
        puVar4 = (undefined4 *)puStack_278[2];
        *puStack_278 = 0;
        puStack_278[1] = 0;
        puStack_278[2] = 0;
        puStack_278 = puVar4;
    }
    
    finalizePacket();
    return;
}