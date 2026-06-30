// FUNC_NAME: NetSession::initializePacketWindow
void __fastcall NetSession::initPacketWindow(uint32_t* pData)
{
    uint32_t* currentSlot; // ebx? actually local pointer
    uint32_t* nodePtr;
    int iterCount;

    // Initialize header fields at the start of the structure
    pData[0] = 0;              // +0x00: mWindowSize / flags
    pData[1] = 0;              // +0x04: mSendSequence
    *(uint16_t*)(pData + 2) = 0; // +0x08: mAckCount (short)
    pData[4] = 0;              // +0x10: mReceiveSequence
    pData[5] = 0;              // +0x14: mFreePacketList (head pointer)
    pData[6] = 0;              // +0x18: mLastReceiveTime

    // Build free list of 24 packet slots, each slot has 6 linked nodes
    currentSlot = pData + 0x120a6; // +0x48298: start of packet window area
    iterCount = 24; // 0x18
    do {
        // Node 0: slot metadata
        currentSlot[-2] = pData[5]; // link to previous head (at +0x14)
        currentSlot[-1] = 0;
        currentSlot[0] = 0;
        currentSlot[1] = 0;

        // Node 1: first subnode (at currentSlot - 0x206)
        currentSlot[-0x206] = (uint32_t)(currentSlot - 2); // +0x4? actually pointer to node0
        currentSlot[-0x205] = 0;
        currentSlot[-0x204] = 0;
        currentSlot[-0x203] = 0;

        // Node 2: second subnode (at currentSlot - 0x40a)
        currentSlot[-0x40a] = (uint32_t)(currentSlot - 0x206);
        currentSlot[-0x409] = 0;
        currentSlot[-0x408] = 0;
        currentSlot[-0x407] = 0;

        // Node 3: third subnode (at currentSlot - 0x60e)
        currentSlot[-0x60e] = (uint32_t)(currentSlot - 0x40a);
        currentSlot[-0x60d] = 0;
        currentSlot[-0x60c] = 0;
        currentSlot[-0x60b] = 0;

        // Node 4: fourth subnode (at currentSlot - 0x812)
        currentSlot[-0x812] = (uint32_t)(currentSlot - 0x60e);
        currentSlot[-0x811] = 0;
        currentSlot[-0x810] = 0;
        currentSlot[-0x80f] = 0;

        // Node 5: top-level node (at currentSlot - 0xa16)
        nodePtr = currentSlot - 0xa16;
        *nodePtr = (uint32_t)(currentSlot - 0x812); // link to node4
        currentSlot[-0xa15] = 0;
        currentSlot[-0xa14] = 0;
        currentSlot[-0xa13] = 0;

        // Move to previous slot (each slot is 0xc18 dwords = 0x3060 bytes)
        currentSlot -= 0xc18;
        iterCount--;
        // Update head of free list to the newly created top node
        pData[5] = nodePtr;
    } while (iterCount != 0);

    // Initialize the incoming packet array (144 entries, each 8 dwords)
    pData = pData + 0x122aa; // +0x48AA8: start of incoming packet buffer
    iterCount = 0x90; // 144
    do {
        pData[-2] = 0;
        pData[-1] = 0;
        pData[0] = 0;
        pData[1] = 0;
        pData[3] = 0; // skip index 2 ? (unused field)
        pData[4] = 0;
        pData += 8; // advance by 32 bytes per entry
        iterCount--;
    } while (iterCount != 0);
}