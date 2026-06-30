// FUNC_NAME: SomeClass::cleanup
void SomeClass::cleanup(void)
{
    // Release child object B (stored at +0x10) via its interface at +0xc
    if (m_pChildB != 0) {
        m_pInterfaceB->releaseChild(m_pChildB, 0); // +0x4 vtable entry (index 1)
        m_pChildB = 0; // +0x10
    }
    // Call cleanup/destructor on interface B (vtable entry +0xc, index 3)
    m_pInterfaceB->cleanup();

    // Release child object A (stored at +0x8) via its interface at +0x4
    if (m_pChildA != 0) {
        m_pInterfaceA->releaseChild(m_pChildA, 0); // +0x4 vtable entry
        m_pChildA = 0; // +0x8
    }
    // Call cleanup/destructor on interface A (vtable entry +0xc)
    m_pInterfaceA->cleanup();
    return;
}