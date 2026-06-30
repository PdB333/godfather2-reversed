// FUNC_NAME: UnknownClass::getPointerAtOffset8
// Function address: 0x00643a80
// Returns this + 8 (likely a pointer to a base class subobject or specific data member)
// Offsets: this+0x00: vtable pointer, this+0x04: unknown, this+0x08: returned pointer
__thiscall int UnknownClass::getPointerAtOffset8(void)
{
    // Return the base address plus 8 bytes
    return reinterpret_cast<int>(this) + 8;
}