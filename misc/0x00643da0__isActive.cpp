// FUNC_NAME: isActive
// Function address: 0x00643da0
// Role: Checks if bit 0 of the flags field at offset +0x4 is set.
// Likely a member function (__thiscall) returning whether the object is active.

uint __thiscall isActive(void* thisPtr)
{
    // Read the flags field at offset 0x4 and return the lowest bit.
    return *(uint*)((char*)thisPtr + 4) & 1;
}