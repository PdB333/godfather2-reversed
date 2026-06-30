// FUNC_NAME: UnknownClass::resetState

void __thiscall UnknownClass::resetState(void)
{
    // Call base initializer (vtable setup, etc.)
    FUN_00652ab0();  // baseInitialize();

    // Zero out a range of flags/state fields
    // Offsets relative to this:
    // +0x78 : m_flagA
    // +0x73 : m_flagB1
    // +0x74 : m_flagB2
    // +0x75 : m_flagB3
    // +0x76 : m_flagB4
    // +0x77 : m_flagB5
    // +0x79 : m_flagC
    // +0x7a : m_flagD
    // +0x7c : m_flagE
    // +0x7d : m_flagF
    this->field_0x78 = 0;
    this->field_0x73 = 0;
    this->field_0x74 = 0;
    this->field_0x75 = 0;
    this->field_0x76 = 0;
    this->field_0x77 = 0;
    this->field_0x79 = 0;
    this->field_0x7a = 0;
    this->field_0x7c = 0;
    this->field_0x7d = 0;

    // Set vtable pointer (likely already set by base initializer, but overwritten)
    *(int **)this = (int *)&PTR_LAB_00e42e68;  // vtable

    // Set an index/handle to -1 (invalid)
    // +0x7b : m_handleIndex
    this->field_0x7b = 0xffffffff;

    return;
}