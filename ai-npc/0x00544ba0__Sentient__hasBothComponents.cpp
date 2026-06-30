// FUNC_NAME: Sentient::hasBothComponents
bool __thiscall Sentient::hasBothComponents(void)
{
    // Check if both important components are present.
    // +0x2D8: m_pFirstComponent (e.g., weapon slot, driver pointer)
    // +0x360: m_pSecondComponent (e.g., inventory, engine pointer)
    if (m_pFirstComponent != nullptr && m_pSecondComponent != nullptr) {
        return true;
    }
    return false;
}