// FUNC_NAME: GhostConnection::buildGhostPacket

int GhostConnection::buildGhostPacket()
{
    // Linked list of packet entries at this+0x70
    PacketNode* currentNode = *(PacketNode**)((uint)this + 0x70);
    int nodesProcessed = 0;

    // First loop: reset state for each packet node
    for (; currentNode != nullptr; currentNode = (PacketNode*)*currentNode) {
        clearPacketNode(currentNode + 8); // FUN_00459280
    }

    // Second loop: process ghost array (each entry 0xB0 bytes)
    int arrayIndex = 0;
    int ghostCount = *(int*)((uint)this + 0x34);
    int packetOffset = 0;

    if (ghostCount != 0) {
        int dummyArray[5] = {0}; // temporary array used for offset tracking
        do {
            // Pointer to current ghost entry (base at this+0x50)
            GhostEntry* ghostEntry = (GhostEntry*)(*(int*)((uint)this + 0x50) + dummyArray[0]);

            if (*(char*)&ghostEntry->flags == '\0') { // flag at offset +6
                // Copy ghost data block (8 dwords) into packet buffer
                // Buffer is selected by this->ghostBufferIndex (byte at +0x2D)
                uint bufferIndex = *(byte*)((uint)this + 0x2D);
                int* destBuffer = *(int**)((uint)this + 0x58 + bufferIndex * 4);
                int* srcData = *(int**)((uint)ghostEntry + 0x20);

                destBuffer[packetOffset + 0] = srcData[0];
                destBuffer[packetOffset + 1] = srcData[1];
                destBuffer[packetOffset + 2] = srcData[2];
                destBuffer[packetOffset + 3] = srcData[3];
                destBuffer[packetOffset + 4] = srcData[4];
                destBuffer[packetOffset + 5] = srcData[5];
                destBuffer[packetOffset + 6] = srcData[6];
                destBuffer[packetOffset + 7] = srcData[7];
            } else {
                // Ghost is destroyed or needs special handling
                GhostState* state = *(GhostState**)((uint)ghostEntry + 0x4C);
                state->flags = 0; // +0x20
                state->oldBuffer = *(int*)((uint)this + 0x58 + (uint)*(byte*)((uint)this + 0x2D) * 4) + packetOffset; // +0x24
                state->newBuffer = *(int*)((uint)this + 0x58 + (uint)*(byte*)((uint)this + 0x2D) * 4) + 0x10 + packetOffset; // +0x28
                finalizeGhostRemoval(*(void**)((uint)this + 0x74), state->uniqueId, ghostEntry->objectId); // FUN_00459400
            }

            dummyArray[0] += 0xB0; // next ghost entry
            ghostCount--;
            packetOffset += 0x20; // size of copied data block (8 dwords)
        } while (ghostCount > 0);
    }

    // Third loop: finalize packet nodes and attach ghost data
    void* globalPtr = PTR_LAB_0110ab24;
    int globalData = DAT_0110ab28;
    for (currentNode = *(PacketNode**)((uint)this + 0x70); currentNode != nullptr; currentNode = (PacketNode*)*currentNode) {
        PTR_LAB_0110ab24 = globalPtr;
        DAT_0110ab28 = globalData;

        // Set reference to ghost's sequence number (offset +100 from some base)
        uint bufferIndex = *(byte*)((uint)this + 0x2D);
        currentNode->ghostSeq = *(int*)(currentNode->somePointer + 100 + bufferIndex * 4); // +4 offset

        // Call function to finalize packet node (likely adds to send queue)
        int* result = sendOrQueuePacket(&nodesProcessed, currentNode, 0, 0, 0, globalPtr, globalData); // FUN_00495510
        currentNode->dataBlock[0] = result[0]; // +8
        currentNode->dataBlock[1] = result[1]; // +9

        nodesProcessed++;
        globalPtr = PTR_LAB_0110ab24;
        globalData = DAT_0110ab28;
    }

    PTR_LAB_0110ab24 = globalPtr;
    DAT_0110ab28 = globalData;
    return nodesProcessed;
}