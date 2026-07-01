// FUNC_NAME: SimObject::init

void __thiscall SimObject::init(SimObject* this, uint param)
{
    // +0xDC: parent pointer
    this->m_pParent = nullptr;
    // +0xB8: stored parameter (e.g., owner or data)
    this->m_pData = (void*)param;
    // +0xC0: next sibling
    this->m_pNext = nullptr;
    // +0xB4: previous sibling
    this->m_pPrev = nullptr;
    // Global initialization call (likely clears shared state)
    FUN_00986240();
}