// FUNC_NAME: EARSObject::assignFromStruct
void __thiscall EARSObject::assignFromStruct(void* this, const uint64_t* source)
{
    // Copy 8-byte field at offset +0x10 from first 8 bytes of source
    *(uint64_t*)((char*)this + 0x10) = source[0];
    // Copy 4-byte field at offset +0x18 from first 4 bytes of second 8-byte block of source
    *(uint32_t*)((char*)this + 0x18) = *(uint32_t*)((const char*)source + 8);
    // Set bit 0x40000000 at offset +0x4 (flags field)
    *(uint32_t*)((char*)this + 0x4) |= 0x40000000;
}