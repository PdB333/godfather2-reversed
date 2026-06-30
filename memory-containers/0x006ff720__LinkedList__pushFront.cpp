// FUNC_NAME: LinkedList::pushFront
// Function address: 0x006FF720
// Role: Inserts a new node at the head of a doubly linked list, using an external allocator.

// Assumed structure layouts:
// Node (0xC bytes):
//   +0x00 int data;        // Value stored in node
//   +0x04 Node* next;      // Forward pointer (to next node)
//   +0x08 Node* prev;      // Backward pointer (to previous node)
//
// List (head of list container, 0x14 bytes):
//   +0x00 Node* head;      // First node in list (most recently inserted)
//   +0x04 Node* tail;      // Last node in list (only set when list is empty)
//   +0x08 int count;       // Number of nodes
//   +0x0C void* allocContext; // Context for the allocator (if null, use global default)
//   +0x10 Allocator* allocator; // Allocator object with virtual allocate function

// Allocator interface (simplified)
class Allocator {
public:
    virtual void* allocate(int size, void* context) = 0;
};

// Extern global default allocator context (from Ghidra data)
extern void* g_defaultAllocatorContext; // DAT_01218a14

// Reconstructed function
void __thiscall LinkedList::pushFront(int value) { // value may be passed in EDX in __fastcall
    // Retrieve or use default allocator context
    void* allocContext = this->allocContext; // param_1[3]
    if (allocContext == nullptr) {
        allocContext = g_defaultAllocatorContext;
    }

    // Allocate a new node via the allocator's virtual function (first vtable entry)
    // The allocator is at offset 0x10, and its vtable is at the beginning of its object
    Node* newNode = static_cast<Node*>(
        (this->allocator->*(this->allocator->vtable[0]))(0xC, allocContext)
    ); // using member function pointer equivalent: this->allocator->allocate(12, allocContext)

    if (newNode != nullptr) {
        newNode->data = value;           // *puVar1 = *unaff_ESI
        newNode->next = nullptr;         // puVar1[2] = 0
        newNode->prev = nullptr;         // puVar1[1] = 0 (but next line overwrites)
    }

    // Link the new node into the list
    newNode->prev = this->head;          // puVar1[1] = *param_1 (old head becomes "prev" of new node)
    if (this->head != nullptr) {
        this->head->next = newNode;      // *(old_head + 8) = puVar1 (old head's "next" points back)
    }

    this->count++;                       // param_1[2] = param_1[2] + 1
    this->head = newNode;                // *param_1 = (int)puVar1

    // If the list was empty, set tail to the new node
    if (this->tail == nullptr) {         // param_1[1] == 0
        this->tail = newNode;            // param_1[1] = (int)puVar1
    }
}