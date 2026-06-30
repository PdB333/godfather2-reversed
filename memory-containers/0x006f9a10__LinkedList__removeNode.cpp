// FUNC_NAME: LinkedList::removeNode

extern void FUN_004daf90(void* ptr);

class Allocator {
public:
    virtual void* allocate(uint size) = 0;        // vtable+0
    virtual void deallocate(void* ptr, uint flags) = 0; // vtable+4
};

struct Node {
    void*        m_data;        // +0x00
    // padding / unknown at +0x04, +0x08
    void*        m_unknown1;    // +0x04
    void*        m_unknown2;    // +0x08
    void         (*m_destructor)(void*); // +0x0C
    void*        m_subObject;   // +0x10
    // padding / unknown at +0x14
    Node*        m_next;        // +0x18
    Node*        m_prev;        // +0x1C
};

class LinkedList {
public:
    Node*        m_head;       // +0x00
    Node*        m_tail;       // +0x04
    int          m_count;      // +0x08
    int          m_unknown;    // +0x0C (unused in this function)
    Allocator*   m_allocator;  // +0x10
};

void __thiscall LinkedList::removeNode(void* thisPtr, int unusedParam, int* nodePtrPtr) {
    LinkedList* list = (LinkedList*)thisPtr;
    Node* node = (Node*)*nodePtrPtr;

    // Advance the iterator to the next node
    if (node != nullptr) {
        *nodePtrPtr = (int)node->m_next;
    } else {
        *nodePtrPtr = 0;
    }

    // Unlink node from the doubly linked list
    if (node == list->m_head) {
        if (node == list->m_tail) {
            // Only node in the list
            list->m_head = nullptr;
            list->m_tail = nullptr;
        } else {
            // Node is head, but not tail
            list->m_head = node->m_next;
            if (node->m_next != nullptr) {
                node->m_next->m_prev = nullptr;
            }
        }
    } else {
        Node* prev = node->m_prev;
        if (node == list->m_tail) {
            // Node is tail, but not head
            list->m_tail = prev;
            if (prev != nullptr) {
                prev->m_next = nullptr;
            }
        } else {
            // Node is in the middle
            prev->m_next = node->m_next;
            node->m_next->m_prev = prev;
        }
    }

    // Destroy the sub‑object stored at offset +0x10
    if (node->m_subObject != nullptr) {
        FUN_004daf90(node->m_subObject);
    }

    // Call the stored destructor for the data pointer
    if (node->m_data != nullptr) {
        node->m_destructor(node->m_data);
    }

    // Deallocate the node memory through the list’s allocator
    list->m_allocator->deallocate(node, 0);

    // Decrement the node count
    list->m_count -= 1;

    // The following line references an unaff_EBX register that should be
    // handled by the calling code; omitted for clarity.
    // *unaff_EBX = *nodePtrPtr;
}