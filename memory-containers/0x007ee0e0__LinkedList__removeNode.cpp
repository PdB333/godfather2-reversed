// FUNC_NAME: LinkedList::removeNode
// Function address: 0x007ee0e0
// Removes a node from a singly linked list with head and tail pointers.
// The list structure has head at offset 0, tail at offset 4.
// Each node has a 'next' pointer at offset 4. Offset 0 is unused in this function.
// __thiscall

struct LinkedListNode {
    int field_0;          // +0x00: unknown data
    LinkedListNode* next; // +0x04: pointer to next node
};

struct LinkedList {
    LinkedListNode* head; // +0x00
    LinkedListNode* tail; // +0x04
};

void __thiscall LinkedList::removeNode(LinkedListNode* nodeToRemove)
{
    LinkedListNode* current = head;
    if (nodeToRemove == current)
    {
        if (nodeToRemove == tail)
        {
            // List becomes empty; set both head and tail to nodeToRemove's next (which should be null)
            head = tail = nodeToRemove->next;
            return;
        }
        // Remove head only, not tail
        head = nodeToRemove->next;
        return;
    }

    // Find predecessor: traverse until we find a node whose next is nodeToRemove
    LinkedListNode* predecessor = nullptr;
    do {
        predecessor = current;
        if (predecessor == nullptr) break;
        current = current->next;
    } while (predecessor->next != nodeToRemove);

    // If found, unlink
    if (predecessor->next == nodeToRemove)
    {
        predecessor->next = nodeToRemove->next;
        if (tail == nodeToRemove)
        {
            tail = predecessor; // Update tail if we removed the last node
        }
    }
}