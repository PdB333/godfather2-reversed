// FUNC_NAME: UnknownClass::getFirstMember
// Function address: 0x008bd990
// Returns the first DWORD of the object (e.g., ID, handle, or internal pointer)

__thiscall unsigned int UnknownClass::getFirstMember(void) const
{
    // The first member of this class is at offset 0x00
    // Return the value directly as an unsigned integer
    return *(unsigned int *)this;
}