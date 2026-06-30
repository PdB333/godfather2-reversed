// FUNC_NAME: OrderedList::insertAt
// Address: 0x00704440
// This function inserts a new empty node at a given index in an ordered list.
// The internal structure uses a dynamic array of 8-byte nodes (prev, next pointers)
// and maintains a doubly linked list order. The array index positions are independent of 
// the linked list order. Inserting at a position shifts the list pointers to make room.
int* __thiscall OrderedList::insert(int* this, unsigned int index) {
    int* data = (int*)this[0]; // +0x00: base pointer to node array
    int size = this[1];        // +0x04: number of nodes
    int capacity = this[2];    // +0x08: capacity of array

    // Grow if full
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        FUN_007041d0(newCapacity); // Grow function (resizes array)
        // After grow, `data` pointer might be stale, but external call updates this[0]
    }

    // Pointer to the new node (end of used array)
    int* newEnd = (int*)(*this + size * 8); // each node is 2 ints = 8 bytes

    if (index != size) {
        // Insert at a position other than end → shift list pointers
        if (newEnd != nullptr) {
            int prevPrev = newEnd[-2]; // previous node's prev (8 bytes back)
            newEnd[0] = prevPrev;      // new node's prev = previous node's prev
            newEnd[1] = 0;             // new node's next = 0
            if (prevPrev != 0) {
                newEnd[1] = *(int*)(prevPrev + 4); // set new node's next to old next of previous
                *(int**)(prevPrev + 4) = newEnd; // update previous node's next to new node
            }
        }

        // Shift nodes from index to size-1 by updating their list pointers
        unsigned int uVar2 = size;
        while (--uVar2, index < uVar2) {
            int* curNode = (int*)(*this + uVar2 * 8);
            // The condition `curNode != curNode - 2` always true; likely a missed optimization
            int prevFirst = curNode[-2];
            if (curNode[0] != prevFirst) {
                if (curNode[0] != 0) {
                    FUN_004daf90(curNode); // cleanup old node pointer
                }
                curNode[0] = prevFirst;
                if (prevFirst != 0) {
                    curNode[1] = *(int*)(prevFirst + 4);
                    *(int**)(prevFirst + 4) = curNode;
                }
            }
        }

        this[1] = size + 1; // increment size

        // Clear the target slot at `index`
        int targetOffset = index * 8;
        if (*(int*)(*this + targetOffset) != 0) {
            FUN_004daf90(*this + targetOffset);
        }
        int* targetSlot = (int*)(*this + targetOffset);
        if (targetSlot != nullptr) {
            targetSlot[0] = 0;
            targetSlot[1] = 0;
        }
        return targetSlot;
    } else {
        // Append at end
        if (newEnd != nullptr) {
            newEnd[0] = 0;
            newEnd[1] = 0;
        }
        this[1] = size + 1;
        return (int*)(*this + size * 8); // return pointer to the newly added slot
    }
}