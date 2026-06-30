// FUNC_NAME: EARS::Core::DoublyLinkedList::pushFront
// Address: 0x0071cd20
// Role: Adds a new node to the front of a doubly linked list, using a memory manager's allocator.

// The list structure:
// offset 0x00: head (Node*)
// offset 0x04: tail (Node*)
// offset 0x08: count (int)
// offset 0x0C: allocatorContext (AllocatorContext*, can be null to use default)
// offset 0x10: memoryManager (MemoryManager*, provides allocate() via vtable)

struct Node {
    int data;       // +0x00
    Node* next;     // +0x04
    Node* prev;     // +0x08
};

struct MemoryManager {
    // Virtual function table
    virtual void* allocate(size_t size, void* allocatorContext) = 0; // First vtable entry
};

class DoublyLinkedList {
public:
    Node* head;                // +0x00
    Node* tail;                // +0x04
    int count;                 // +0x08
    void* allocatorContext;    // +0x0C
    MemoryManager* memMgr;     // +0x10

    void __thiscall pushFront(int data) {
        Node* newNode = nullptr;
        void* ctx = allocatorContext;
        if (ctx == nullptr) {
            ctx = (void*)0x01218a14; // Global default allocator context
        }
        newNode = (Node*)memMgr->allocate(0xC, ctx); // Allocate 12 bytes for new node

        if (newNode != nullptr) {
            newNode->data = data;
            newNode->prev = nullptr;   // puVar1[2] = 0
            newNode->next = nullptr;   // puVar1[1] = 0
        }
        // Actually the order in the decompiled: first set *newNode = *unaff_ESI (data), then set puVar1[2]=0, then puVar1[1]=0
        // The data is passed in register ESI (unaff_ESI). We assume data is an integer.
        // The call to memMgr->allocate is: (*(code *)**(undefined4 **)this->memMgr)(0xc, ctx);
        // That matches a virtual call with size and context.

        // Now link new node into the list
        newNode->next = head;   // puVar1[1] = *param_1 (head)
        if (head != nullptr) {
            head->prev = newNode;   // *(oldHead + 8) = newNode
        }
        count++;                // param_1[2] = param_1[2] + 1
        head = newNode;         // *param_1 = newNode
        if (tail == nullptr) {  // if param_1[1] == 0
            tail = newNode;     // param_1[1] = newNode
        }
    }
};