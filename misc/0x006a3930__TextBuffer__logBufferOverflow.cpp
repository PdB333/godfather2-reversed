// FUNC_NAME: TextBuffer::logBufferOverflow
void __thiscall TextBuffer::logBufferOverflow(int textPosition) {
    // +0x4: pointer to a Logger object with virtual functions (vtable slot 1 is log)
    if (m_logger != nullptr) {
        wchar_t buffer[40]; // 80 bytes wide char buffer
        // Format the error message (external function from the EARS engine)
        formatWideString(buffer, L"E02: The text near %d didn't fit in the buffer", textPosition);
        // Call the logger's virtual method (vtable offset +0x4)
        m_logger->log(buffer);
    }
}