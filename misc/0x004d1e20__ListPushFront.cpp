// FUNC_NAME: ListPushFront
// Function at 0x004d1e20: Doubly linked list insertion at head.
// Inserts a node at the front of a doubly linked list.
// List structure: [head pointer at +0x00, tail pointer at +0x04]
// Node structure: [next pointer at +0x00, prev pointer at +0x04]
void __fastcall ListPushFront(int* node, int* list)
{
    // node->next = list->head
    node[0] = list[0];
    // node->prev = NULL
    node[1] = 0;

    if (list[0] != 0) {
        // List not empty: old head's prev points to new node
        *(int**)(list[0] + 4) = node;
        // Update head to new node
        list[0] = (int)node;
    } else {
        // List empty: both head and tail become new node
        list[1] = (int)node;
        list[0] = (int)node;
    }
}