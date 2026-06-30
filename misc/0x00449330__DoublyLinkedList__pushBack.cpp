// FUNC_NAME: DoublyLinkedList::pushBack
// 0x00449330: Inserts a node at the end of a doubly linked list.
// List structure: +0x0 = head pointer, +0x4 = tail pointer.
// Node structure: +0x0 = next pointer, +0x4 = prev pointer.
void __fastcall DoublyLinkedList::pushBack(Node* node)
{
    // node is passed in EAX? Actually __fastcall: first param (likely this) in ECX, second (node) in EDX.
    // Ghidra shows param_1 as list pointer, in_EAX as node. We reconstruct accordingly.

    Node* list = this; // param_1 / this
    // Node* node = ... (passed in EDX)

    node->next = nullptr;          // *node = 0
    node->prev = list->tail;       // node[1] = list->tail (param_1[1])

    if (list->tail != nullptr) {
        list->tail->next = node;   // tail->next = node
    } else {
        list->head = node;         // first node: head = node
    }
    list->tail = node;             // update tail to new node
}