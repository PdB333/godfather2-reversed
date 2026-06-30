// FUNC_NAME: Array::getElement
// Address: 0x00700090
// Role: Returns the element at a given index from an array stored at offset +0x4 in this object.
// Each element is 4 bytes. This is a raw accessor for an embedded array.

uint32_t __thiscall Array::getElement(int index) const
{
    // Array data is at this+0x4; each entry is 4 bytes.
    return *(uint32_t *)((uint32_t)this + 4 + index * 4);
}