// FUNC_NAME: CUnknownClass::~CUnknownClass
void * __thiscall CUnknownClass::~CUnknownClass(CUnknownClass *this, byte deleteFlag) {
    // Set vtable to real vtable (derived class)
    *this = &PTR_FUN_00d654d0;

    // Destroy dynamically allocated sub-object (if any)
    if (this->m_pSubObject != (void *)0x0) {
        destroySubObject(this->m_pSubObject);
        this->m_pSubObject = (void *)0x0;
    }

    // Set vtable to purecall to prevent calls to destroyed object
    *this = &PTR___purecall_00e407a4;

    // If delete flag is set, deallocate memory for this (operator delete)
    if ((deleteFlag & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}