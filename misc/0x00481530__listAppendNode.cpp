// FUNC_NAME: listAppendNode
void __fastcall listAppendNode(ListNode* node)
{
    // Global head and tail of a doubly-linked list (offsets: +4 prev, +8 next)
    ListNode* head = s_listHead;  // DAT_0120e9f4
    ListNode* tail = s_listTail;  // DAT_0120e9f8

    // Only add if node is not already the head and is currently unlinked (next == 0)
    if (head != node && node->next == nullptr) {
        node->prev = nullptr;          // New node becomes the new tail
        node->next = tail;             // Its next points to the old tail (if any)
        head = node;
        tail = node;

        if (s_listTail != nullptr) {
            // Old tail's prev now points to the new node
            s_listTail->prev = node;
            s_listTail = node;
            return;
        }
    }

    // Update globals (for empty list case or when no insertion occurred)
    s_listTail = tail;
    s_listHead = head;
}