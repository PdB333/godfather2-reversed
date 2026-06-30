// FUNC_NAME: BaseObject::tryActivate
// Function at 0x00624d00: Checks flag bit 2 and a data pointer, then calls internal activate function.
// __thiscall
// +0x14: byte m_flags (bit 2 = some condition)
// +0x18: void* m_pData (likely a pointer to action data or target)
bool __thiscall BaseObject::tryActivate()
{
    // Only proceed if bit 2 is clear and data pointer is non-null
    if ((m_flags & 2) == 0 && m_pData != nullptr)
    {
        activateInternal(); // Calls FUN_00624f30 – processes the object's action/data
        return true;
    }
    return false;
}