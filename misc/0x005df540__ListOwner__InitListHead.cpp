// FUNC_NAME: ListOwner::InitListHead
// Function at 0x005df540: Initialize a self-referential linked list head node in the owner object.
// Assumes this pointer (owner) in ESI, and a resource container pointer in EAX (passed implicitly).

struct ListNode {
    ListNode* prev;       // +0x00
    ListNode* next;       // +0x04
    void*    data;        // +0x08 (often points to self for head)
    char     flag;        // +0x15 (set to 1 for head node)
    // ... other fields
};

struct ResourceContainer {
    void** vtable;        // +0x00 (pointer to virtual function table)
    int    handle;        // +0x04 (resource handle, can be 0)
};

struct ListOwner {
    ListNode* listHead;   // +0x1c
    int       listCount;  // +0x20
    // ... other fields
};

// External helper functions (known from callee addresses)
extern ListNode* AllocateListNode(void);                  // 0x005e0b10
extern int DuplicateResource(int handle, void* basePtr);  // 0x004265d0
extern void InitializeNode(void* owner, void* basePtr, int handle); // 0x005e0170

void ListOwner::InitListHead(ResourceContainer* container)
{
    // Extract base pointer and resource handle from the container
    void* basePtr = (void*)*container;               // first field is a vtable pointer or similar
    int resourceHandle = container->handle;          // second field

    // Call virtual function at vtable offset +8 (index 2) on the base object
    // (basePtr points to a struct with a vtable; the function is called with basePtr as this)
    void (*vfunc)(void*) = (void (*)(void*))((void***)basePtr)[2]; // vtable[2]
    vfunc(basePtr);

    // Duplicate the resource handle if it is non-zero
    int dupHandle = 0;
    if (resourceHandle != 0) {
        dupHandle = DuplicateResource(resourceHandle, basePtr);
    }

    // Initialize some internal node (likely links the container to the owner)
    InitializeNode(this, basePtr, dupHandle);

    // Allocate a new list node from the node pool
    ListNode* newNode = AllocateListNode();

    // Store the node as the list head at offset 0x1c
    this->listHead = newNode;

    // Set flag to indicate head node (offset 0x15)
    newNode->flag = 1;

    // Make the node self-referential: set prev, next, and data to itself
    newNode->prev = newNode;   // +0x00
    newNode->next = newNode;   // +0x04
    newNode->data = newNode;   // +0x08

    // Initialize the list count to 0 at offset 0x20
    this->listCount = 0;
}