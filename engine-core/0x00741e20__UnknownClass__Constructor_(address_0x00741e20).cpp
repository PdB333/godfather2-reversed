// FUNC_NAME: UnknownClass::Constructor (address 0x00741e20)
// Initializes a small object with a vtable pointer and several data fields.
// Field layout (based on this pointer as uint*):
//   +0x00: vtable pointer (4 bytes)
//   +0x04: int (param2)
//   +0x08: __int64 or double (param3) — stored as 8 bytes at offsets 8-15
//   +0x10: int (param4)
//   +0x14: int (param5)
//   +0x18: byte (param6)
// The class is at least 0x19 bytes, likely padded to 0x1C or 0x20.

void __thiscall Constructor(void* thisPtr, int param2, __int64 param3, int param4, int param5, char param6)
{
    uint* this = (uint*)thisPtr;

    this[0] = (uint)&PTR_LAB_00d63b44;                 // vtable pointer
    this[1] = (uint)param2;                             // offset +0x04
    *(__int64*)(this + 2) = param3;                     // offset +0x08 (8 bytes)
    this[4] = (uint)param4;                             // offset +0x10
    this[5] = (uint)param5;                             // offset +0x14
    *(char*)((int)this + 0x18) = param6;                // offset +0x18 (byte)

    return;
}