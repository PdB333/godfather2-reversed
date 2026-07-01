// FUNC_NAME: Array::insertAt
// Address: 0x00792ac0
// Inserts a new element at the given index, shifting subsequent elements to the right.
// Returns a pointer to the newly inserted element slot.

int __thiscall Array::insertAt(int *this, uint index)
{
    int *data = (int *)this[0];          // +0x00: pointer to element array
    int size = this[1];                  // +0x04: current number of elements
    int capacity = this[2];              // +0x08: allocated capacity

    // Reallocate if full
    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        reallocate(newCapacity);         // FUN_007924c0
    }

    // If inserting not at the end, shift elements to make room
    if (index != (uint)size) {
        // Shift element at index-1 to index? Actually copy first field and then call something
        Element *slot = (Element *)(data + index * 4); // each element is 16 bytes (4 ints)
        slot->field0 = slot[-1].field0;   // copy first field from previous element
        elementCopyConstruct(&slot[-1]);  // FUN_00792150: likely copy construct on previous element

        // Shift remaining elements from end down to index+1
        int lastIdx = size - 1;
        if (index < (uint)lastIdx) {
            int offset = lastIdx * 4;     // offset in ints
            int count = lastIdx - index;
            do {
                Element *cur = (Element *)(data + offset);
                cur->field0 = (cur - 1)->field0;  // copy first field from element before
                elementMoveConstruct(cur - 1);    // FUN_00792320: likely move construct
                offset -= 4;                      // move to previous element
                count--;
            } while (count != 0);
        }

        // Update size
        this[1] = size + 1;

        // Destroy old content at the new slot (if any) and zero it out
        int slotOffset = index * 4;
        Element *newSlot = (Element *)(data + slotOffset);
        if (newSlot->field1 != 0) {
            elementDestruct(newSlot->field1); // FUN_009c8f10: destroy pointed object
        }
        newSlot->field1 = 0;
        newSlot->field2 = 0;
        newSlot->field3 = 0;

        return (int)newSlot;
    }
    else {
        // Appending at end: just zero out the new slot and increment size
        Element *newSlot = (Element *)(data + size * 4);
        newSlot->field1 = 0;
        newSlot->field2 = 0;
        newSlot->field3 = 0;
        this[1] = size + 1;
        return (int)newSlot;
    }
}