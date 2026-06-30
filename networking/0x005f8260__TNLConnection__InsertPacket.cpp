// FUNC_NAME: TNLConnection::InsertPacket
// Address: 0x005f8260
// This function inserts a packet node into a sorted linked list within a packet window.
// The structure at 'this' contains:
//   +0x00: basePtr (int) - base for descriptor lookups
//   +0x08: nodeArray (int*) - pointer to array of Node structures (stride 0xC)
// The packet node (newNode) has layout:
//   +0x00: next pointer (int)
//   +0x04: float value (stored as int)
//   +0x0B: byte flag
// The loop traverses until a sentinel pointer (param_3) is reached.

void __thiscall TNLConnection::InsertPacket(int *this, int *newNode, int sentinelPtr) {
    int *const originalThis = this;
    int basePtr = *this;                        // +0x00
    int *currNode = newNode;                   // start with the node to insert

    if (g_EaxReg != sentinelPtr) {             // g_EaxReg is a register variable (likely ECX or hidden this)
        do {
            float *descriptor = (float *)GetDescriptor(basePtr, g_EaxReg);  // look up descriptor
            // descriptor +0x00: float, +0x04: ushort used for indexing
            g_EaxReg = *(int *)(basePtr + 0x20) + (uint)*(unsigned short *)(descriptor + 1) * 0x24;

            int *nodeArray = (int *)originalThis[2];          // +0x08
            int nodeIndex = (g_EaxReg - *(int *)(*originalThis + 0x20)) / 0x24;
            float existingVal = *(float *)((int)nodeArray + 4 + nodeIndex * 0xC);
            int *nextNode = (int *)((int)nodeArray + nodeIndex * 0xC);

            // Copy byte flag from newNode to located node
            *(char *)((int)nextNode + 0xB) = *(char *)((int)newNode + 0xB);

            float newVal = (float)currNode[1];
            float desVal = *descriptor;
            if ((existingVal <= 0.0f) || (newVal + desVal <= existingVal)) {
                *nextNode = (int)currNode;             // update next pointer
                nextNode[1] = (int)(newVal + desVal);  // update value
            }
            currNode = nextNode;
        } while (g_EaxReg != sentinelPtr);
    }
}