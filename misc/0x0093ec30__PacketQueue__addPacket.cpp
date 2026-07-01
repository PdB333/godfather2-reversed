// FUNC_NAME: PacketQueue::addPacket
// Reconstructed C++ for function 0x0093ec30
// Class: PacketQueue (inferred from offsets)
// Role: Adds a new packet to the queue, reusing a free node if available, or allocating one if the queue is not full and conditions permit.

void __thiscall PacketQueue::addPacket(int param_2, int param_3)
{
    // Offset +0x50: count of active nodes (max 20)
    // Offset +0x44: pointer to head of free node list
    // Offset +0x40: pointer to tail of allocated node list? (or secondary queue)
    // Offset +0x34: flags (bit 0 checked if allocated list is non-empty)
    // Offset +0x20: total packets processed counter
    // Offset +0x1c: available slot counter (decremented)
    PacketNode* freeNode;

    if (*(uint*)(this + 0x50) < 20)
    {
        // If the allocated list is empty, or the tail pointer is null and the flag indicates we can allocate more nodes,
        // allocate a new node (FUN_004de190).
        if ((*(int*)(this + 0x44) == 0) &&
            ((*(int*)(this + 0x40) == 0 || ((*(byte*)(this + 0x34) & 1) == 0))))
        {
            allocateNewNode();  // FUN_004de190
        }

        freeNode = *(PacketNode**)(this + 0x44);
        if (freeNode != 0)
        {
            // Remove node from free list:
            // Advance head to next node
            *(int*)(this + 0x20) += 1;           // Increment processed count
            *(int*)(this + 0x1c) -= 1;           // Decrement available slots
            *(int*)(this + 0x44) = freeNode->next; // Update head to next free node

            // Initialize the node fields:
            freeNode->data1 = param_2;            // +0x20 (puVar1[8])
            freeNode->data2 = param_3;            // +0x24 (puVar1[9])
            freeNode->next = 0;                   // +0x00
            freeNode->prev = 0;                   // +0x04
            freeNode->type = 3;                   // +0x08
            freeNode->field_0x10 = 1;             // +0x10 (short)
            freeNode->field_0x12 = 0;             // +0x12 (short)
            freeNode->field_0x14 = 15000;         // +0x14 (short, lower 2 bytes)
            freeNode->field_0x18 = 0;             // +0x18 (int)
            freeNode->field_0x1c = 0;             // +0x1c (int)
            freeNode->timestamp = s_baseTime + 12000; // +0x0C (DAT_01205224 + 12000)

            // Process the newly initialized node (FUN_0093e4c0)
            processNode(freeNode);
        }
    }
}