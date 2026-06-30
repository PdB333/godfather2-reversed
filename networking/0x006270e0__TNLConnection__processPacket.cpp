// FUNC_NAME: TNLConnection::processPacket
void TNLConnection::processPacket(void)
{
    byte savedState; // +0x31
    int *packetList; // +0x10 -> +0x14
    int *currentPacket; // from list
    int *nodeEntry; // from hash table
    int *foundEntry; // result of search
    int stackPtr; // +0x8 (stack pointer)
    int hashTable; // +0x10 -> +0x5c
    int hashIndex; // computed from packet data

    savedState = *(byte *)(this + 0x31);
    *(int *)(this + 8) = *(int *)(this + 8) + 8; // push something on stack
    *(byte *)(this + 0x31) = 0; // clear state flag

    if (*(int *)(*(int *)(this + 0x10) + 0x14) == 0) {
        // No packets to process, restore state and return
        *(byte *)(this + 0x31) = savedState;
        *(int *)(this + 8) = *(int *)(this + 8) - 8;
        return;
    }

    do {
        // Pop packet from list (linked list at +0x14)
        currentPacket = *(int **)(*(int *)(this + 0x10) + 0x14);
        *(int *)(*(int *)(this + 0x10) + 0x14) = *currentPacket;
        *currentPacket = *(int *)(*(int *)(this + 0x10) + 0x10);
        *(int **)(*(int *)(this + 0x10) + 0x10) = currentPacket;

        // Push packet type 7 onto stack
        stackPtr = *(int *)(this + 8);
        *(int *)(stackPtr - 8) = 7;
        *(int **)(stackPtr - 4) = currentPacket;

        // Mark packet as processed (clear low 2 bits of byte at +5)
        *(byte *)((int)currentPacket + 5) = *(byte *)((int)currentPacket + 5) & 0xfc;

        // Check if packet already has flag 0x04 set
        if ((*(byte *)(currentPacket[2] + 6) & 4) == 0) {
            // Search hash table for matching entry
            hashTable = *(int *)(*(int *)(this + 0x10) + 0x5c);
            hashIndex = (1 << (*(byte *)(currentPacket[2] + 7) & 0x1f)) - 1U & *(uint *)(hashTable + 8);
            nodeEntry = (int *)(*(int *)(currentPacket[2] + 0x10) + hashIndex * 0x14);

            do {
                if ((*nodeEntry == 4) && (nodeEntry[1] == hashTable)) {
                    foundEntry = nodeEntry + 2;
                    if (nodeEntry[2] != 0) goto LAB_00627178;
                    break;
                }
                nodeEntry = (int *)nodeEntry[4];
            } while (nodeEntry != (int *)0x0);

            // Mark packet as needing processing
            *(byte *)(currentPacket[2] + 6) = *(byte *)(currentPacket[2] + 6) | 4;
        }
        foundEntry = (int *)0x0;

LAB_00627178:
        if (foundEntry != (int *)0x0) {
            // Copy data from found entry to stack
            nodeEntry = *(int **)(this + 8);
            *nodeEntry = *foundEntry;
            nodeEntry[1] = foundEntry[1];

            // Push packet reference and type
            stackPtr = *(int *)(this + 8);
            *(int **)(stackPtr + 0xc) = currentPacket;
            *(int *)(stackPtr + 8) = 7;

            // Advance stack pointer
            *(int *)(this + 8) = *(int *)(this + 8) + 0x10;

            // Call packet handler
            FUN_006362d0();
        }

        if (*(int *)(*(int *)(this + 0x10) + 0x14) == 0) {
            // No more packets, restore state and return
            *(int *)(this + 8) = *(int *)(this + 8) - 8;
            *(byte *)(this + 0x31) = savedState;
            return;
        }
    } while (true);
}