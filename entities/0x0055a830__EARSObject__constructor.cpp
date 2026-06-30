// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(EARSObject *this)
{
    // Call base class constructor (virtual base at offset -4)
    baseClassConstructor((int)this - 4);
    // Additional initialization
    postConstructInit();
    // Initialize field at +0x30 to 0 (likely a pointer or flag)
    this->field_0x30 = 0; // +0x30: m_pNext / m_bInitialized
}