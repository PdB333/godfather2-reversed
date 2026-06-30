// FUNC_NAME: ShortArray::ShortArray
// Address: 0x005b8c50
// Purpose: Constructor for a short (uint16) array with small buffer optimization.
// Structure offsets (relative to this):
// +0x00 : capacity (int)
// +0x04 : size (int)
// +0x08 : data pointer (int*) - points to internal buffer if capacity <= 15, else heap
// +0x0C : internal buffer (16 shorts / 32 bytes) - used when capacity <= 15

void __thiscall ShortArray::ShortArray(int capacity)
{
    // Internal buffer location (offset +0x0C)
    int* internalBuffer = this + 3; // +0x0C in bytes

    // Set data pointer to internal buffer initially
    this[2] = (int)internalBuffer; // +0x08

    this[0] = capacity; // +0x00
    this[1] = capacity; // +0x04 (size set to capacity, placeholder)

    // Zero out first two shorts of internal buffer
    internalBuffer[0] = 0; // offset +0x0C
    internalBuffer[1] = 0; // offset +0x10

    // Zero out remaining internal buffer (shorts at +0x14 through +0x28)
    this[5] = 0; // +0x14
    this[6] = 0; // +0x18
    this[7] = 0; // +0x1C
    this[8] = 0; // +0x20
    this[9] = 0; // +0x24
    this[10] = 0; // +0x28

    // Internal initialization (likely sets up some state)
    initializeInternalBuffer(this, capacity > 0 ? 1 : 0); // FUN_0059c140

    // Allocate heap buffer if capacity exceeds small buffer limit (15)
    if (capacity > 15)
    {
        int allocatedSize = capacity + 1; // one extra for null terminator
        int* heapBuffer = nullptr;
        if (allocatedSize != 0)
        {
            // Heap allocation: 2 bytes per element
            heapBuffer = (int*)heapAlloc(allocatedSize * 2, 0); // DAT_0119caf0 function
        }
        this[2] = (int)heapBuffer; // set data pointer to heap
    }

    // Zero out all elements (including the null terminator)
    if (capacity > 0)
    {
        for (int i = 0; i < capacity; i++)
        {
            *(short*)(this[2] + i * 2) = 0;
        }
    }
    // Null terminate the array (one extra element)
    *(short*)(this[2] + capacity * 2) = 0;

    // Set size to capacity (overwrites previous size)
    this[1] = capacity;
}