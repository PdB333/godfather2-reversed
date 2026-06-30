// FUNC_NAME: getBaseOffset8
int __fastcall getBaseOffset8(int thisPtr)
{
    // Returns this+8, typically to access a member at offset 0x8 (e.g., a base class pointer or a vtable extension)
    return thisPtr + 8;
}