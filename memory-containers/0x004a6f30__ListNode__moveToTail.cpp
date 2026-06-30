// FUNC_NAME: ListNode::moveToTail
// Role: Removes this node from a doubly linked list and reinserts it at the tail.
// Struct offsets: +0x0 = pData (unused here), +0x4 = pPrev, +0x8 = pNext
// Globals: g_pListHead (0x01205490), g_pListTail (0x01205494)
void ListNode::moveToTail(void)
{
    ListNode* pPrev = reinterpret_cast<ListNode*>(this->pPrev);
    ListNode* pNext = reinterpret_cast<ListNode*>(this->pNext);

    // Unlink from current position
    if (pPrev != nullptr)
    {
        pPrev->pNext = pNext;
    }
    if (pNext != nullptr)
    {
        pNext->pPrev = pPrev;
    }

    // Update head/tail pointers if this was at either end
    if (g_pListHead == this)
    {
        g_pListHead = pNext;
    }
    if (g_pListTail == this)
    {
        g_pListTail = pPrev;
    }

    // Clear own links
    this->pNext = nullptr;
    this->pPrev = nullptr;

    // Reinsert at tail
    if (g_pListTail != nullptr)
    {
        g_pListTail->pNext = this;
        this->pPrev = reinterpret_cast<uintptr_t>(g_pListTail); // raw pointer stored as integer
        this->pNext = nullptr;
        g_pListTail = this;
    }
    else
    {
        // List was empty, this becomes only element
        g_pListHead = this;
        this->pPrev = nullptr;
        this->pNext = nullptr;
        g_pListTail = this;
    }
}