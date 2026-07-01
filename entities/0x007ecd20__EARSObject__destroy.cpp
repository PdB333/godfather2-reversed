// FUNC_NAME: EARSObject::destroy
// Function address: 0x007ecd20
// Role: Releases a child object (at offset +0x4) and then calls a base cleanup virtual function (vtable+0xc).
// This is likely a destructor or final cleanup method for an EARS engine object.

void __thiscall EARSObject::destroy(void)
{
    // Check if the child pointer (offset +0x4) is non-null
    if (this->m_pChild != 0)
    {
        // Call virtual function at vtable+4 on the child object with flag 0 (release)
        this->m_pChild->release(0);
        // Clear the child pointer
        this->m_pChild = 0;
    }
    // Call virtual function at vtable+0xc (base cleanup/destructor)
    this->cleanup();
}