// FUNC_NAME: DoublyLinkedList::removeNode
// Address: 0x0071cda0

class DoublyLinkedList {
public:
    struct Node {
        // +0x00: possibly data pointer/value, not accessed here
        Node* next; // +0x04
        Node* prev; // +0x08
    };

    Node* head;       // +0x00
    Node* tail;       // +0x04
    int size;         // +0x08
    void* allocator;  // +0x10 (object with vtable at +0x00, free method at vtable+0x04)

    // Removes the node pointed to by *nodePtr and advances *nodePtr to the next node.
    // param_2 is unused (likely a flag for incomplete type erasure).
    void __thiscall removeNode(Node** nodePtr, int /*unused*/) {
        Node* nodeToRemove = *nodePtr;
        Node* next = (nodeToRemove) ? nodeToRemove->next : nullptr;
        *nodePtr = next;

        if (nodeToRemove == head) {
            if (nodeToRemove == tail) {
                tail = nullptr;
                head = nullptr;
            } else {
                head = next;
                if (next) {
                    next->prev = nullptr;
                }
            }
        } else {
            Node* prev = nodeToRemove->prev;
            if (nodeToRemove == tail) {
                tail = prev;
                if (prev) {
                    prev->next = nullptr;  // set tail->next = 0
                }
            } else {
                prev->next = next;
                next->prev = prev;
            }
        }

        // Deallocate node via allocator (vtable+4 → free(node, 0))
        typedef void (__thiscall *FreeFunc)(void*, void*, int);
        FreeFunc freeFunc = *(FreeFunc*)(*(int*)allocator + 4);
        freeFunc(allocator, nodeToRemove, 0);
        size--;
    }
};