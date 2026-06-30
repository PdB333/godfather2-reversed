// FUNC_NAME: CGenericBase::CGenericBase

struct CGenericBase {
    void** vtable;         // +0x00
    void*  m_pAllocated;   // +0x04
    int    m_field8;       // +0x08
    int    m_field12;      // +0x0C
    int    m_param2;       // +0x10
    int    m_param3;       // +0x14
    int    m_param4;       // +0x18
    int    m_param5Flags;  // +0x1C (low byte used)
};

// Constructor: stores four parameters (three ints + a byte flag) and initializes internal fields
CGenericBase* __thiscall CGenericBase::CGenericBase(CGenericBase* this,
                                                    int param2,
                                                    int param3,
                                                    int param4,
                                                    char param5)
{
    // Save pointer to the allocated memory field (offset 0x04)
    void** pAllocField = &this->m_pAllocated;

    // Set vtable pointer
    this->vtable = (void**)&PTR_LAB_00d653d4;

    // Zero internal fields
    this->m_pAllocated = NULL;
    this->m_field8 = 0;
    this->m_field12 = 0;

    // If previously allocated, free it (FUN_004daf90 likely frees the memory and NULLs the pointer)
    if (this->m_pAllocated != NULL) {
        FUN_004daf90(pAllocField);    // passes address of the pointer
        this->m_pAllocated = NULL;    // reassign to NULL
    }

    // Set field again (redundant, probably for safety)
    this->m_field12 = 0;

    // Store constructor arguments
    this->m_param2 = param2;
    *reinterpret_cast<char*>(&this->m_param5Flags) = param5;  // write byte at offset 0x1C
    this->m_param3 = param3;
    this->m_param4 = param4;

    return this;
}