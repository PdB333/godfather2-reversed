// FUNC_NAME: EARSObjectArray::pushBack
// Reconstructed C++ for EA EARS engine array class (dynamic array with copy-construction)
// This function inserts a new element (size 0x20) at the end of the array, resizing if needed.

void __thiscall EARSObjectArray::pushBack(int *this, int sourceObject)
{
    int currentSize = this[1]; // current number of elements
    int capacity = this[2];    // allocated capacity

    if (currentSize == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Reallocate internal buffer (FUN_004bcac0 likely allocates new memory and copies old elements)
        FUN_004bcac0(capacity); // this is a member function call? Possibly reallocate(this, capacity)
    }

    // Pointer to where the new element will be placed (offset = currentSize * 0x20)
    undefined4 *newElementSlot = (undefined4 *)(this[1] * 0x20 + this[0]);

    // Increment the count
    this[1] = this[1] + 1;

    if (newElementSlot != (undefined4 *)0x0) {
        // Set vtable pointer for the new element (all objects share the same vtable)
        *newElementSlot = &PTR_LAB_00e35c24;
        // Copy the 7 dwords of data starting at offset 4 from source object
        newElementSlot[1] = *(undefined4 *)(sourceObject + 4);
        newElementSlot[2] = *(undefined4 *)(sourceObject + 8);
        newElementSlot[3] = *(undefined4 *)(sourceObject + 0xc);
        newElementSlot[4] = *(undefined4 *)(sourceObject + 0x10);
        newElementSlot[5] = *(undefined4 *)(sourceObject + 0x14);
        newElementSlot[6] = *(undefined4 *)(sourceObject + 0x18);
        newElementSlot[7] = *(undefined4 *)(sourceObject + 0x1c);
    }
    return;
}