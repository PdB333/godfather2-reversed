// FUNC_NAME: BaseObject::initFields
void __thiscall BaseObject::initFields() {
    // +0x7c: set from a global constant (likely a pointer or identifier)
    this->m_pGlobalRef = static_cast<void*>(DAT_00d5ccf8);
    // +0x80: clear field (probably a pointer or flag)
    this->m_pSelf = nullptr;
}