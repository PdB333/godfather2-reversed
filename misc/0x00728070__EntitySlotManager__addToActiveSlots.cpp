// FUNC_NAME: EntitySlotManager::addToActiveSlots
// Address: 0x00728070
// Role: For each active slot (0-3), insert the object's internal linked list node (at offset +0x48) into the slot's dynamic array.
// The class has 4 sets of dynamic array metadata (base pointer, count, capacity) stored at this+0x10 to this+0x3C.
// Each dynamic array entry is 8 bytes: [pointer to node, next pointer].

void __thiscall EntitySlotManager::addToActiveSlots(int thisPtr, int objectPtr)
{
    // Pointer to the count field of slot 0; advancing by 3 ints moves to next slot's metadata block.
    int *slotCountPtr = (int *)(thisPtr + 0x14);
    int slotIdx = 0;

    do {
        char slotActive = FUN_007260a0(slotIdx); // Check if this slot is enabled
        if (slotActive != 0) {
            // Get the node that lives at objectPtr + 0x48 (likely a member of the object's list node structure)
            int *objNode;
            if (objectPtr == 0) {
                objNode = 0;
            } else {
                objNode = (int *)(objectPtr + 0x48);
            }

            int savedNext = 0;
            // Temporarily replace the node's next pointer with a pointer to the local objNode variable
            // (used for safe insertion or to mark ownership)
            if (objNode != 0) {
                savedNext = *(int *)(objNode + 1);  // save original next pointer
                *(int **)(objNode + 1) = &objNode;   // point next to stack address of objNode
            }

            int currentCount = slotCountPtr[0];   // current number of entries in this slot's array
            int currentCapacity = slotCountPtr[1]; // capacity

            // Grow the array if full
            if (currentCount == currentCapacity) {
                int newCap;
                if (currentCapacity == 0) {
                    newCap = 1;
                } else {
                    newCap = currentCapacity * 2;
                }
                FUN_00727cc0(newCap);  // Reallocate or set new capacity
            }

            // Get base pointer to the array of 8-byte entries
            int *arrayBase = (int *)slotCountPtr[-1];
            // Compute address of the new entry
            int *newEntry = (int *)((char *)arrayBase + currentCount * 8);
            // Increment count
            slotCountPtr[0] = currentCount + 1;

            if (newEntry != 0) {
                newEntry[0] = (int)objNode;   // Store pointer to the object's node
                newEntry[1] = 0;               // Initialize next pointer
                if (objNode != 0) {
                    newEntry[1] = savedNext;                 // Restore original next from node
                    *(int **)(objNode + 1) = newEntry;       // Link node to this new entry
                }
            }

            // Cleanup: possibly remove the temporary linkage, decrement reference, etc.
            if (objNode != 0) {
                FUN_004daf90(&objNode);
            }
        }

        slotIdx++;
        slotCountPtr += 3;  // Move to the next slot: each block is 12 bytes (3 ints)
    } while (slotIdx < 4);
}