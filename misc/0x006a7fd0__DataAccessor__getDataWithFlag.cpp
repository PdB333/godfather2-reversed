// FUNC_NAME: DataAccessor::getDataWithFlag
uint __thiscall DataAccessor::getDataWithFlag(uint *outValue) {
    // this is param_1 (int*)
    // Structure layout:
    // +0x00: SomeOtherStruct* m_pOwner
    // +0x04: uint* m_pData
    uint result = in_EAX & 0xffffff00; // Preserve upper 24 bits of EAX (likely caller's return code)
    
    if (m_pData != nullptr && m_pOwner != nullptr && *(char*)(m_pOwner + 6) == '\x02') {
        // m_pOwner->field_6 == 2 indicates valid data
        *outValue = *m_pData;
        // Encode value: upper 8 bits = 1 (success flag), lower 24 bits = (value >> 8)
        result = (1 << 24) | ((*m_pData >> 8) & 0xFFFFFF);
    }
    return result;
}