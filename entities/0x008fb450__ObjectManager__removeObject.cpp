// FUNC_NAME: ObjectManager::removeObject
// Address: 0x008fb450
// Role: Removes an object from the manager's internal list and linked list.
// The object has an embedded linked list node at offset +0x48 (next pointer) and +0x4c (prev_next pointer).
// The manager stores an array of pairs at +0x94 (each pair is 8 bytes, first element is the node's next pointer address) with count at +0x98.

void __thiscall ObjectManager::removeObject(int thisPtr, int objPtr)
{
    uint index;
    uint foundIndex;
    int* pairPtr;
    int nodeNextPtr;       // Address of the object's next pointer field (objPtr + 0x48)
    int oldPrevNext;       // Saved value of the object's prev_next pointer (objPtr + 0x4c)

    if (objPtr != 0) {
        nodeNextPtr = objPtr + 0x48;                     // +0x48: next pointer field
        oldPrevNext = 0;
        if (nodeNextPtr != 0) {
            oldPrevNext = *(int*)(objPtr + 0x4c);        // +0x4c: prev_next pointer (points to previous node's next field)
            *(int**)(objPtr + 0x4c) = &nodeNextPtr;      // Temporarily update prev_next to point to local variable (for removal)
        }

        // Search the manager's array for an entry matching nodeNextPtr
        index = 0;
        foundIndex = 0xffffffff;
        if (*(uint*)(thisPtr + 0x98) != 0) {             // +0x98: array count
            pairPtr = *(int**)(thisPtr + 0x94);          // +0x94: pointer to array of pairs (each pair is 2 ints)
            do {
                foundIndex = index;
                if (*pairPtr == nodeNextPtr) break;      // Compare first element of pair
                index = index + 1;
                pairPtr = pairPtr + 2;                   // Move to next pair (8 bytes)
                foundIndex = 0xffffffff;
            } while (index < *(uint*)(thisPtr + 0x98));
        }

        // Remove the node from the linked list (using the local pointer)
        if (nodeNextPtr != 0) {
            removeFromLinkedList(&nodeNextPtr);          // FUN_004daf90
        }

        // If found in the array, remove the entry and finalize object removal
        if (-1 < (int)foundIndex) {
            removeArrayEntry(foundIndex);                // FUN_0083ca20
            finalizeObjectRemoval(objPtr);               // FUN_0083f190
        }
    }
    return;
}