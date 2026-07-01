// FUNC_NAME: AsyncEventProcessor::processResult
int32_t AsyncEventProcessor::processResult(uint32_t param_1, uint32_t param_2) {
    uint32_t local_10[3] = {0, 0, 0};
    char result = checkCondition(param_1, local_10);
    if (result != 0) {
        handleData(local_10, param_2);
        if (local_10[0] != 0) {
            // Callback stored at +0x04? Actually local_4 is uninitialized in decomp, 
            // but likely it's a member function pointer or vtable entry.
            // For reconstruction, we assume it's a member variable stored at offset +0x04
            // or a function pointer passed via some other means.
            // Since the decompiled shows it as a local variable, we keep as is but note.
            // In practice, this would be a member variable (e.g., m_callback).
            if (m_callback != nullptr) {
                m_callback(local_10[0]);
            }
        }
        return 1;
    }
    if (local_10[0] != 0) {
        if (m_callback != nullptr) {
            m_callback(local_10[0]);
        }
    }
    return 0;
}