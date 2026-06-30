// FUNC_NAME: NodeList::insertAfter
// Function at 0x0060d480: Inserts a new node after the current node in a doubly-linked list.
// The class has a pointer to a node as its first member (m_pCurrentNode).
// Global variables manage the list head, count, and allocator.

struct Node {
    void* value; // +0x00
    Node* next;  // +0x04
    Node* prev;  // +0x08
};

// Global allocator context (default or custom)
extern void* g_pAllocatorContext; // DAT_012224ec
extern int g_nodeCount;          // DAT_012224e8
extern Node* g_pListHead;        // DAT_012224e0
extern void** g_pAllocatorVtable; // DAT_012224f0 (pointer to vtable)
extern void* g_defaultAllocatorContext; // DAT_01218a14

class NodeList {
public:
    Node* m_pCurrentNode; // +0x00

    // __thiscall
    // param_1: pointer to a pointer that will receive the new node (output)
    // value: the value to store in the new node (originally unaff_retaddr)
    void* insertAfter(void** outNewNode, void* value) {
        Node* current = m_pCurrentNode; // *in_EAX
        Node* newNode;

        // Determine allocator context
        void* allocContext = g_defaultAllocatorContext;
        if (g_pAllocatorContext != nullptr) {
            allocContext = g_pAllocatorContext;
        }

        // Allocate node (size 0xC = 12 bytes)
        newNode = (Node*)((*(void* (*)(int, void*))*g_pAllocatorVtable)(0xC, allocContext));
        if (newNode != nullptr) {
            newNode->value = value; // *unaff_retaddr (value pointer)
            newNode->next = nullptr;
            newNode->prev = nullptr;
        }

        // Insert after current node
        if (current == g_pListHead) {
            // Inserting after head: new node becomes new head
            newNode->prev = nullptr;
            g_pListHead = newNode;
        } else {
            // Standard double-linked list insertion
            newNode->prev = current->prev;
            current->prev->next = newNode;
        }
        newNode->next = current;
        current->prev = newNode;

        g_nodeCount++;

        *outNewNode = newNode;
        return outNewNode;
    }
};