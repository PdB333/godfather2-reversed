// FUNC_NAME: DynamicArray::DynamicArray
// Address: 0x006e5fa0
// Constructor for a dynamic array of 4-byte elements. Allocates and zero-initializes the buffer.

void* __cdecl AllocateMemory(uint32_t size); // from FUN_009c8e80, underlying heap allocator

class DynamicArray {
public:
    void* pArray;      // +0x00
    uint32_t count;    // +0x04 (number of elements)
    uint32_t zero;     // +0x08 (always set to 0)
    uint8_t flags;     // +0x0C
    // total logical size: 13 bytes, but likely padded to 16
};

DynamicArray* __thiscall DynamicArray::DynamicArray(DynamicArray* this, uint32_t elementCount, uint8_t initFlags)
{
    this->flags = initFlags;               // +0x0C
    this->count = elementCount;            // +0x04
    this->pArray = nullptr;                // +0x00
    this->zero = 0;                        // +0x08

    uint32_t allocSize = elementCount * 4; // each element is 4 bytes
    void* buffer = AllocateMemory(allocSize);
    this->pArray = buffer;

    memset(buffer, 0, this->count * 4);
    return this;
}