// FUNC_NAME: SomeClass::GetFlagMask
// Address: 0x007078d0
// Role: Returns the given flag bitmask if a condition (checked via virtual method at vtable+0x10) is true, else returns 0.
// The virtual method signature: char __thiscall CheckFlag(uint flag, uint* out)
// out parameter is unused in the caller.

uint SomeClass::GetFlagMask(uint flag)
{
    uint out = 0;                               // local_4, output placeholder
    // Call virtual method at vtable offset 0x10 (index 4)
    char result = (*(char (__thiscall**)(SomeClass*, uint, uint*))(*(uint**)this + 4))(this, flag, &out);
    // If result is non-zero, return the original flag; otherwise return 0
    return (result != 0) ? flag : 0;
}