// FUNC_NAME: LinkedListNode::removeFromList
// Address: 0x006fbc70
// Removes this node from a doubly-linked list and updates the global head if needed.
// Node layout: +0x08 = prev pointer, +0x0C = next pointer
// Global head stored at DAT_0112aaa8 (g_head)
void __fastcall LinkedListNode::removeFromList(LinkedListNode* node)
{
    // Relink the previous node to skip over this one
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
    // Relink the next node to skip back over this one
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    // If this node was the head, move head to the next node
    if (g_head == node) {
        g_head = node->next;
    }
}