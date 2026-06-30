// FUNC_NAME: Variant::getUintValue
uint __fastcall Variant::getUintValue(void* thisPtr) // offset +4 value, +6 type discriminator
{
    // Check type field at +6: if equal to 0x25E3 (likely kType_UShort), value is 16-bit
    if (*(short*)((char*)thisPtr + 6) == 0x25E3)
    {
        // Return low 16 bits of the value field as unsigned int
        return (uint)*(ushort*)((char*)thisPtr + 4);
    }
    // Otherwise value is a full 32-bit unsigned integer
    return *(uint*)((char*)thisPtr + 4);
}