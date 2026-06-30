// FUNC_NAME: checkObjectTypeMatch
uint __thiscall checkObjectTypeMatch(uint eaxValue, uint expectedTypeIdB) const
{
    // +0x14: m_pObjectA (SomeInternalObject*)
    // +0x18: m_pObjectB (SomeInternalObject*)
    // +0x54 on object: m_typeId (uint)

    uint result = eaxValue & 0xFFFFFF00;
    if (m_pObjectA != nullptr && m_pObjectB != nullptr)
    {
        if (m_pObjectA->m_typeId == 0x637b907 && m_pObjectB->m_typeId == expectedTypeIdB)
        {
            // Match: combine typeIdB >> 8 with low byte set to 1
            return (m_pObjectB->m_typeId >> 8) | 1;
        }
        // No match: keep cleared low byte
    }
    return result;
}