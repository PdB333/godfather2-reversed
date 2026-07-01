// FUNC_NAME: GameEntity::getSomeInternalValue
uint GameEntity::getSomeInternalValue() __thiscall
{
    uint result = 0;
    // Offset +0x9c: m_pInternalData pointer
    if (m_pInternalData != nullptr && m_pInternalData != (SomeInternalType*)0x48 && m_pInternalData != nullptr)
    {
        // Offset +0x1ea0: m_nSomeFlag from the internal structure
        result = m_pInternalData->m_nSomeFlag;
    }
    return result;
}