// FUNC_NAME: SomeClass::cleanup
void SomeClass::cleanup()
{
    // +0x58: m_pResource1 (pointer to owned sub-object)
    if (m_pResource1 != 0) {
        releaseSubObject(m_pResource1); // FUN_009c8f10
    }
    // +0x4C: m_pResource2
    if (m_pResource2 != 0) {
        releaseSubObject(m_pResource2); // FUN_009c8f10
    }
    // Base class cleanup / global reset
    baseCleanup(); // FUN_005c16e0
}