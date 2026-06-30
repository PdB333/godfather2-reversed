// FUNC_NAME: Node::init
void __thiscall Node::init(void)
{
    // +0x04: m_pNext (next pointer)
    this->m_pNext = 0;

    // Call sub-object initialization function on the data pointer (+0x00)
    FUN_009c8f10(this->m_pData);

    // +0x00: m_pData (pointer to contained object)
    this->m_pData = 0;

    // +0x08: m_pPrev (previous pointer)
    this->m_pPrev = 0;
}