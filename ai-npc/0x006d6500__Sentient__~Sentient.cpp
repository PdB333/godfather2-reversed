// FUNC_NAME: Sentient::~Sentient
void __thiscall Sentient::~Sentient(Sentient* this)
{
    // Set vtable and RTTI pointers for base class destruction
    this->vtable = (int*)&PTR_FUN_00d5f500;      // vtable at +0x0
    this->rtti = (int*)&PTR_LAB_00d5f4f8;        // likely RTTI pointer at +0x8

    // Destroy subcomponents if allocated
    if (this->m_pComponent0x98 != 0)              // some component at +0x98
        safeDelete(this->m_pComponent0x98);
    if (this->m_pComponent0x5f != 0)              // component at +0x5f
        safeDelete(this->m_pComponent0x5f);
    if (this->m_pComponent0x5d != 0)              // component at +0x5d
        safeDelete(this->m_pComponent0x5d);
    if (this->m_pComponent0x3c != 0)              // component at +0x3c
        safeDelete(this->m_pComponent0x3c);
    if (this->m_pComponent0x3a != 0)              // component at +0x3a
        safeDelete(this->m_pComponent0x3a);

    // Call base class destructor (likely SimObject or Entity)
    FUN_006c9820();
}