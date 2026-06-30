// FUNC_NAME: GrowingArray::allocateElement
// Function at 0x004a7c70: Allocates a new 16-byte element in a dynamic array, resizing if necessary.
// Returns pointer to the newly allocated element (base + oldCount * 0x10).
// Structure layout (this):
//   +0x00: base pointer (int*)
//   +0x04: count (int) – number of elements currently used
//   +0x08: capacity (int) – number of elements allocated (max before resize)
// Each element is 16 bytes (0x10):
//   +0x00: int (maybe pointer)
//   +0x04: short (2 bytes)
//   +0x08: int
//   +0x0C: int

__declspec(naked) void* __thiscall GrowingArray::allocateElement() // returns void* to new element
{
    __asm
    {
        // This function would be compiled as normal; we just reconstruct the logic.
        // The actual implementation is in the decompiled code.
        // Placeholder for symbols.
    }
}

// Reconstructed C++ logic (the actual code would be in a real translation unit):
void* GrowingArray::allocateElement()
{
    // this is in EAX
    int* base = this->base;       // *(int**)this = [0x00]
    int& count = this->count;     // this[1] = [0x04]
    int& capacity = this->capacity; // this[2] = [0x08]

    if (count == capacity)
    {
        // Need to grow
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;

        // Resize internal buffer to new capacity (calls FUN_004a7bf0)
        this->resize(capacity); // FUN_004a7bf0 takes new capacity as parameter
    }

    // Pointer to the element at index 'count'
    void* element = reinterpret_cast<char*>(base) + count * 0x10;

    if (element != nullptr)
    {
        // Zero out the new element (16 bytes)
        *(int*)element = 0;
        *(short*)((char*)element + 4) = 0;
        *(int*)((char*)element + 8) = 0;
        *(int*)((char*)element + 12) = 0;
    }

    int oldCount = count;
    count++;

    // Return pointer to the allocated element
    return reinterpret_cast<char*>(base) + oldCount * 0x10;
}