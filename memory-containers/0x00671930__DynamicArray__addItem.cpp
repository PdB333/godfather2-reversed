// FUNC_NAME: DynamicArray::addItem
// Address: 0x00671930
// This function adds an item (param_1) to a dynamic array of 12-byte elements.
// The array structure is:
//   +0x00: ushort count
//   +0x02: pointer to element array (allocated or reallocated)
// The element structure:
//   +0x00: (unknown, not set here)
//   +0x04: itemId (param_1)
//   +0x08: nextIndex (set to 0)
// Returns a handle/index via param_2 (output).

void __thiscall DynamicArray::addItem(int this, uint itemId, uint *outHandle)
{
    ushort count = *(ushort *)this;               // +0x00: current count
    uint *buffer;                                  // pointer to element array

    *outHandle = 0;                                // default to 0

    if (count == 0) {
        // First allocation
        buffer = (uint *)FUN_00673070();           // allocate initial buffer
    } else {
        // Reallocate to hold count+1 elements (12 bytes each)
        buffer = (uint *)FUN_006730f0(*(int *)(this + 2), (count + 1) * 12 - 12);
    }

    *(int *)(this + 2) = (int)buffer;              // +0x02: store new buffer pointer

    // Store the item at the end of the array
    int elemBase = (int)buffer + 4 + count * 12;   // skip first 4 bytes of element?
    *(uint *)(elemBase) = itemId;                  // +0x04 of element
    *(uint *)(elemBase + 4) = 0;                   // +0x08 of element

    *(ushort *)this = count + 1;                   // increment count

    uint handle = FUN_006721d0();                  // generate new handle
    *outHandle = handle;                           // return handle
    return;
}