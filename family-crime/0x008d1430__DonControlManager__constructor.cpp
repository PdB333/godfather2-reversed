// FUNC_NAME: DonControlManager::constructor
// Function address: 0x008d1430
// Constructor for DonControlManager - initializes virtual table,
// releases any existing child object (offset +0x28), updates interface pointer,
// resets global state and calls global initialization.

void __fastcall DonControlManager::constructor(DonControlManager* this)
{
    // +0x00: virtual table pointer
    *(void**)this = (void*)&PTR_FUN_00d7d050;
    // +0x0C: interface/type descriptor pointer (set to initial value)
    this->m_pInterface = &PTR_LAB_00d7d04c;

    // +0x28: child object pointer (may be non-null if reinitializing)
    if (this->m_pChild != 0)
    {
        // +0x34: function pointer stored in this object (likely destructor for child)
        (*(void (__fastcall*)(void*))this->m_childDestructor)(this->m_pChild);
    }

    // +0x0C: update interface pointer after cleanup
    this->m_pInterface = &PTR_LAB_00d7d048;

    // Reset global flag (indicates manager is now inactive/ready for init)
    g_bDonControlManagerActive = 0;

    // Perform global initialization (likely registers with engine)
    FUN_004083d0();
}