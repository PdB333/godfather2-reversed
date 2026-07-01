// FUNC_NAME: SomeClass::getDataByIndex
// Address: 0x00907680
// Role: Returns a 32-bit value from an array of up to 45 (0x2D) elements stored in the object.
// The object has a pointer at +0x04 to a contiguous array of uint32 values.
// If the index is out of bounds (>= 45), returns 0.

uint32 __thiscall getDataByIndex(void* this, uint32 index)
{
    // +0x04: pointer to array of uint32 values
    if (index < 0x2D) {
        return *(uint32*)(*(int*)((char*)this + 4) + index * 4);
    }
    return 0;
}