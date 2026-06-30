// FUNC_NAME: FourFieldStruct::SetFromArray
// Function address: 0x006f17c0
// Copies 4 DWORDs from a source array into the object's fields at offsets +4..+10.
// Note: Offset +0 (likely vtable pointer) is not modified.
void __thiscall FourFieldStruct::SetFromArray(void* this, const uint32_t* src)
{
    // +0x04: first data field
    *(uint32_t*)((int)this + 0x04) = src[0];
    // +0x08: second data field
    *(uint32_t*)((int)this + 0x08) = src[1];
    // +0x0C: third data field
    *(uint32_t*)((int)this + 0x0C) = src[2];
    // +0x10: fourth data field
    *(uint32_t*)((int)this + 0x10) = src[3];
}