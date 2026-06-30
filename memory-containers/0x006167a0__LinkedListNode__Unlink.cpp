// FUNC_NAME: LinkedListNode::Unlink
// Address: 0x006167a0
// Unlinks a node from a doubly linked list and performs global manager cleanup.

void __thiscall LinkedListNode::Unlink(int this)
{
    int* pGlobalManager = (int*)0x01205968; // global manager singleton

    // Global manager update (e.g., decrement reference count)
    FUN_00617270();

    // If a certain global flag is not set, perform additional cleanup
    if (*(int*)(pGlobalManager + 0x814) == 0) {
        FUN_006171a0();
    }

    // Unlink from doubly linked list
    // Offsets: this+0x3C = prev, this+0x40 = next
    if (*(int**)(this + 0x40) != 0) {
        *(int*)(*(int*)(this + 0x40) + 0x3C) = *(int*)(this + 0x3C); // next->prev = this->prev
    }
    if (*(int*)(this + 0x3C) != 0) {
        *(int*)(*(int*)(this + 0x3C) + 0x40) = *(int*)(this + 0x40); // prev->next = this->next
    }

    // Clear node fields
    *(int*)(this + 0x3C) = 0; // m_pPrev = NULL
    *(int*)(this + 0x40) = 0; // m_pNext = NULL
    *(int*)(this + 0x30) = 0; // m_pData = NULL (or other pointer)
}