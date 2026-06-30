// FUNC_NAME: LinkedList::append
// Address: 0x004d1e40
// Role: Appends a node to the tail of a doubly linked list.
// Node structure: +0x00 next, +0x04 prev
// List structure: +0x00 head, +0x04 tail
// Calling convention: custom __fastcall (ECX = list pointer, EAX = node pointer)

void __fastcall LinkedList_append(LinkedList* list, Node* node)
{
    // Set node's next to null (becomes new tail)
    node->next = nullptr;
    // Link node's prev to current tail
    node->prev = list->tail;

    if (list->tail != nullptr)
    {
        // If list is not empty, current tail's next becomes this node
        list->tail->next = node;
        // Update tail to the new node
        list->tail = node;
        return;
    }
    // Empty list: node becomes both head and tail
    list->head = node;
    list->tail = node;
}