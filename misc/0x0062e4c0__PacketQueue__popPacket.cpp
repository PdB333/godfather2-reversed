// FUNC_NAME: PacketQueue::popPacket
// Function address: 0x0062e4c0
// Purpose: Dequeue a packet from a packet buffer (TNL-like network layer)
// Returns: 1 if no packet available, 2 if packet removed successfully

undefined4 PacketQueue::popPacket(void)
{
    int *pWritePtr; // +0xc: write pointer (tail)
    undefined4 *pData;
    int iStatus;
    undefined4 *pDest;
    undefined4 uPacketType;
    int iBytes;
    
    pWritePtr = *(int **)(this + 0xc);
    // Check if queue is not empty: writePtr < readPtr (wrapped buffer) and not null
    if ((pWritePtr < *(int **)(this + 8)) && (pWritePtr != (int *)0x0))
    {
        if (*pWritePtr == 4) {
            // Type 4: packet data is at offset 0x10 from the data pointer
            iBytes = pWritePtr[1] + 0x10;
        }
        else {
            iStatus = checkBufferFull(this); // FUN_00633990
            if (iStatus == 0) {
                iBytes = 0;
            }
            else {
                iBytes = pWritePtr[1] + 0x10;
            }
            // Check if buffer is at capacity; if so, grow it
            if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24))
            {
                growBuffer(); // FUN_00627360
            }
        }
        if (iBytes == 0) goto LAB_0062e50f;
    }
    else {
LAB_0062e50f:
        assertFail("PacketQueue::pop - queue is empty"); // FUN_00627ac0 with string
    }
    
    // Second read: extract packet type from the same position
    pWritePtr = *(int **)(this + 0xc);
    if ((pWritePtr < *(int **)(this + 8)) && (pWritePtr != (int *)0x0))
    {
        if (*pWritePtr == 4) {
            uPacketType = *(undefined4 *)(pWritePtr[1] + 0xc);
        }
        else {
            iStatus = checkBufferFull(this); // FUN_00633990
            if (iStatus == 0) {
                uPacketType = 0;
            }
            else {
                uPacketType = *(undefined4 *)(pWritePtr[1] + 0xc);
            }
        }
    }
    else {
        uPacketType = 0;
    }
    
    // Shift elements in the buffer to remove the first packet
    iBytes = *(int *)(this + 0xc);
    pWritePtr = (int *)(iBytes + 8);
    if (((pWritePtr < *(int **)(this + 8)) && (pWritePtr != (int *)0x0)) && (0 < *pWritePtr))
    {
        if ((pWritePtr < *(int **)(this + 8)) && (pWritePtr != (int *)0x0))
        {
            if (*pWritePtr == 4) {
                iBytes = *(int *)(iBytes + 0xc) + 0x10;
            }
            else {
                iStatus = checkBufferFull(this); // FUN_00633990
                if (iStatus == 0) {
                    iBytes = 0;
                }
                else {
                    iBytes = *(int *)(iBytes + 0xc) + 0x10;
                }
                if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24))
                {
                    growBuffer(); // FUN_00627360
                }
            }
            if (iBytes != 0) goto LAB_0062e5c9;
        }
        assertFail("PacketQueue::pop - queue is empty"); // FUN_00627ac0 with string
    }
LAB_0062e5c9:
    // Process the packet
    iStatus = processPacket(this, uPacketType); // FUN_00629280
    if (iStatus == 0) {
        return 1; // No packet processed
    }
    
    // Remove the packet from the front by shifting elements
    **(undefined4 **)(this + 8) = 0; // Clear head pointer? Actually set first element to 0
    *(int *)(this + 8) = *(int *)(this + 8) + 8; // Advance head by 8 bytes (one element)
    pDest = *(undefined4 **)(this + 8);
    for (puVar4 = pDest; pDest + -4 < puVar4; puVar4 = puVar4 + -2) {
        *pDest = puVar4[-2];
        pDest[1] = puVar4[-1];
    }
    pDest = *(undefined4 **)(this + 8);
    pDest[-4] = *pDest;
    pDest[-3] = pDest[1];
    return 2; // Packet removed
}