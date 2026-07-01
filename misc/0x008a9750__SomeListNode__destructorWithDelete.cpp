// FUNC_NAME: SomeListNode::destructorWithDelete
int __thiscall SomeListNode::destructorWithDelete(byte param_2)
{
    // +0x28: vtable pointer
    this->vtable = &PTR_LAB_00e317cc;

    // +0x18: m_pPrev (previous node pointer)
    // +0x1c: m_pNext (next node pointer)
    // +0x20: m_pData (arbitrary data pointer, in this context used as a replacement node)

    if (this->m_pPrev != 0) {
        if (this->m_pNext == 0) {
            // No next node: set previous node's "next" (offset +4) to m_pData
            *(int *)(this->m_pPrev + 4) = this->m_pData;
        } else {
            // Has next node: set next node's "prev" (offset +8) to m_pData
            *(int *)(this->m_pNext + 8) = this->m_pData;
        }
        if (this->m_pData != 0) {
            // Set m_pData's "prev" (offset +4) to m_pNext
            *(int *)(this->m_pData + 4) = this->m_pNext;
        }
    }

    // Base destructor / cleanup
    FUN_0064d150();

    if ((param_2 & 1) != 0) {
        // Operator delete
        FUN_009c8eb0(this);
    }

    return this;
}