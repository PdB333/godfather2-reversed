// FUNC_NAME: ListContainer::initialize
// Address: 0x005fb610
// Identified as a constructor/destructor for a doubly linked list container with custom allocator support.
// The class has a base subobject (vtable at +0x0) and an allocator pointer (+0x4).
// Allocates a 12-byte node (prev, next, data) and initializes the list.

// Forward declarations
struct ListNode;
struct SomeBase; // Base class with virtual functions
struct AllocatorContext; // Context for memory allocation

// Node structure: 12 bytes
struct ListNode {
    ListNode* prev; // +0x0
    ListNode* next; // +0x4
    int data;       // +0x8
};

// The container class (partial layout)
class ListContainer {
public:
    SomeBase* m_base;          // +0x0 (pointer to base subobject)
    AllocatorContext* m_alloc; // +0x4 (pointer to allocator context)
    // ... other fields (offsets 0x8, 0xc, 0x10, 0x14, 0x18, 0x1c)
    ListNode* m_head;          // +0x18 (offset 6)
    int m_count;               // +0x1c (offset 7)

    // Constructor-like initialization
    ListContainer* initialize();
};

// External functions used
extern int FUN_004265d0(AllocatorContext* ctx, SomeBase* base); // Some allocation preparation
extern void FUN_005fbd30(ListContainer* self, SomeBase* base, int result); // Additional init

ListContainer* ListContainer::initialize() {
    SomeBase* base = m_base;                  // piVar4 = *this
    AllocatorContext* ctx = m_alloc;          // iVar3 = this[1]

    // Call virtual function at vtable+8 on the base subobject
    base->someVirtualFunc();                  // (**(code **)(*piVar4 + 8))(piVar4)

    int allocResult;
    if (ctx == 0) {
        allocResult = 0;
    } else {
        allocResult = FUN_004265d0(ctx, base);
    }

    FUN_005fbd30(this, base, allocResult);

    // Determine the allocator context (use stack fallback if null)
    AllocatorContext* allocator = m_alloc;    // puVar2 = this[1]
    AllocatorContext stackFallback[3];        // uStack_c, uStack_8, uStack_4
    if (allocator == 0) {
        stackFallback[0] = 0;
        stackFallback[1] = 0;
        stackFallback[2] = 0;
        allocator = &stackFallback;           // puVar2 = &uStack_c
    }

    // Allocate a new node (12 bytes) using the first virtual function of this class
    ListNode* newNode = (ListNode*)(this->vtable[0])(0xc, allocator); // (*(code **)**(undefined4 **)*this)(0xc, puVar2)

    if (newNode != 0) {
        newNode->prev = newNode;              // *(int *)iVar3 = iVar3
    }

    // Ensure the next pointer is also set (self-reference)
    if (newNode->next != 0) {                 // Actually checks if &newNode->next is non-null, but pointer arithmetic is used
        newNode->next = newNode;              // *(int *)(iVar3 + 4) = iVar3
    }

    // Initialize list head and count
    m_head = newNode;                         // this[6] = iVar3
    m_count = 0;                              // this[7] = 0

    return this;
}