// FUNC_NAME: EARS::Modules::ManagerBase::ManagerBase

// Class definition (fields documented with offsets)
struct ManagerBase {
    void**        m_vtable;          // +0x00 (vtable pointer)
    void*         m_funcTable1;      // +0x3C (pointer to function table)
    void*         m_funcTable2;      // +0x48 (pointer to another function table)
    // Sub-object at +0x50 (size 8 bytes, managed by FUN_004086d0 / FUN_00408310)
    char          m_subObj1[8];      // +0x50
    // Sub-object at +0x58 (size 8 bytes, managed by FUN_00408310)
    char          m_subObj2[8];      // +0x58
    void*         m_dataPtr;         // +0x60 (pointer to managed resource)
    void          (*m_destroyFunc)(void*); // +0x6C (cleanup callback for m_dataPtr)
};

void __thiscall ManagerBase::ManagerBase(ManagerBase* this)
{
    // Initialize vtable and function pointers
    this->m_vtable     = &PTR_FUN_00d8c42c;  // set vtable
    this->m_funcTable1 = &PTR_LAB_00d8c41c;  // set function table 1
    this->m_funcTable2 = &PTR_LAB_00d8c418;  // set function table 2

    // Initialize sub-object at +0x50 (constructor call)
    FUN_004086d0(&this->m_subObj1);
    // Additional sub-object initialization (maybe copy construction or two-phase init)
    FUN_00408310(&this->m_subObj1);

    // Initialize secondary sub-object at +0x58
    FUN_00408310(&this->m_subObj2);

    // Release any existing managed resource (e.g., if called after a prior initialization)
    if (this->m_dataPtr != 0) {
        (this->m_destroyFunc)(this->m_dataPtr);
    }

    // Global state update (likely incrementing a reference counter or doing engine housekeeping)
    FUN_0046c640();
}