// FUNC_NAME: GrowingArray12::pushBack

void __thiscall GrowingArray12::pushBack(void *this, const Element12 *elem)
{
    // this is a pointer to a struct with layout:
    // +0x00: Element12* data;   // pointer to array of 12-byte elements
    // +0x04: int count;         // number of elements stored
    // +0x08: int capacity;      // allocated capacity (number of elements)
    int *fields = (int *)this;
    Element12 *data = (Element12 *)fields[0];
    int count = fields[1];
    int capacity = fields[2];

    if (count == capacity) {
        // Grow capacity: double or set to 1 if zero
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate internal buffer (FUN_00817810 takes new capacity in elements)
        fields[2] = growContainer(newCapacity); // updates capacity and possibly data pointer
        data = (Element12 *)fields[0];
    }

    // Copy 12 bytes from elem to next slot
    Element12 *slot = &data[count];
    if (slot != nullptr) {
        slot->first8 = elem->first8;
        slot->last4 = elem->last4;
    }
    fields[1] = count + 1; // increment count
}