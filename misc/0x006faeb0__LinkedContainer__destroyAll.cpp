// FUNC_NAME: LinkedContainer::destroyAll
void __thiscall LinkedContainer::destroyAll(void)
{
    // +0x00: pointer to head of singly-linked list (next pointer at +0x08)
    // +0x0C: pointer to a separate managed object
    // +0x10: pointer to a custom deleter/allocator object (vtable at *m_deleter)

    Node* pNode = this->m_head;
    while (pNode != nullptr)
    {
        Node* pNext = pNode->m_next;             // +0x08: next in chain
        this->m_deleter->release(pNode, 0);      // vtable+0x04: release(node, flag)
        pNode = pNext;
    }
    if (this->m_extra != nullptr)
    {
        this->m_deleter->release(this->m_extra, 0); // release the extra object
    }
    this->m_deleter->cleanup();                     // vtable+0x0C: final cleanup
}