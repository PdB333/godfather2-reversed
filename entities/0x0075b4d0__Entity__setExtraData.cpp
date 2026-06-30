// FUNC_NAME: Entity::setExtraData
void __thiscall Entity::setExtraData(uint32_t* pData) {
    // +0x80: flags field, set bit 1 (value 2) to indicate extra data is present
    m_flags |= 0x2;
    // +0x88: store the value pointed to by pData (likely pointer or handle)
    m_extraData = *pData;
}