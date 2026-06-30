// FUNC_NAME: SomeClass::releaseSubobject
void SomeClass::releaseSubobject() {
    // Check if the sub-object pointer at offset 0x19c is valid
    if (m_pSubobject != nullptr) {
        // Call the free/delete routine for the sub-object
        FreeSubobject(m_pSubobject);
        // Clear the pointer to avoid dangling references
        m_pSubobject = nullptr;
    }
}