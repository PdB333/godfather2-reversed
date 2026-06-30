// FUNC_NAME: EARSObject::EARSObject
// Constructor for base EARS object. Zeros first 16 bytes and initializes version string.
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this) {
    // +0x00: m_field0
    // +0x04: m_field4
    // +0x08: m_field8
    // +0x0C: m_fieldC
    this->m_field0 = 0;
    this->m_field4 = 0;
    this->m_field8 = 0;
    this->m_fieldC = 0;

    // Set version to "v1.00"
    this->setVersion("v1.00");
    return this;
}