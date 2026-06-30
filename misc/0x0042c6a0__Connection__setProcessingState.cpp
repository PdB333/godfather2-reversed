// FUNC_NAME: Connection::setProcessingState
void Connection::setProcessingState(void)
{
    bool bEnable;

    // Check global processing disabled flag or local state already set to 1
    if (DAT_01205358 == '\0' || m_processingState[0x39F8] == 1) { // offset 0x39F8 (0xe7e * 4)
        bEnable = false;
    }
    else {
        // Reset some internal counter/index at offset based on m_descriptor
        m_descriptorTable[m_descriptor + 5] = -1; // offset: m_descriptor + 5 words from start
        bEnable = true;
        // Call virtual function on sub-object (type 2 = disable?)
        m_subObject->vtable->func0x18(m_subObject, 2); // vtable offset 0x18
    }

    // Common helper call
    FUN_004c76e0();

    // Re-enable if previously disabled
    if (bEnable) {
        m_subObject->vtable->func0x18(m_subObject, 1); // type 1 = enable?
    }
}