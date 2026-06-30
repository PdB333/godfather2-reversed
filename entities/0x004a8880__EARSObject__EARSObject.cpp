// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject() {
    // Set vtable to derived class vtable (offset +0x0)
    this->vtable = &s_vtableEARSObject;

    // Call base class constructor (FUN_00454ec0)
    BaseClass::BaseClass();

    // If child object exists and flags byte at +0x3c has bit0 clear, reset child's +0x0c and call virtual method at vtable+0x60
    if ((this->m_pChild != 0) && ((this->m_flags & 1) == 0)) {
        // Clear child's field at offset 0x0c
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this->m_pChild) + 0x0c) = 0;
        // Call virtual function at vtable index 0x18 (offset 0x60/4) on child
        (this->m_pChild->vtable[0x18])(this->m_pChild);
    }

    // Check flags at +0x30: if bit1 (0x02) is clear, call internal initialization (FUN_00453ca0)
    if ((this->m_flags2 & 2) == 0) {
        FUN_00453ca0(this);
    }

    // Finalize construction (FUN_0064d5b0)
    FUN_0064d5b0(this);
}