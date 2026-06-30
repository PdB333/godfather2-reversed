// FUNC_NAME: ListManager::insertNodeAfter
// Address: 0x0060d260
/* 
   Inserts a new 12-byte node into a doubly linked list after the node pointed to by this.
   The new node stores a value (likely the return address of the caller) at offset 0.
   Global list variables:
   - g_pAllocatorFunc: allocation function (usually from vtable)
   - g_pAllocatorPool: memory pool parameter for allocator (0 if uninitialized -> uses g_defaultPool)
   - g_pListHead: head of list
   - g_listCount: number of nodes in list
*/

struct ListNode {
    void* value;           // +0x00
    ListNode* prev;        // +0x04
    ListNode* next;        // +0x08
};

// Global allocator function pointer and pool
extern void* (*g_pAllocatorFunc)(size_t size, void* pool);
extern void* g_pAllocatorPool;
extern void* g_defaultPool; // DAT_01218a14

void* __thiscall ListManager::insertNodeAfter(ListNode*& outHandle) {
    ListNode* currentNode = reinterpret_cast<ListNode*>(this);
    void* pool = g_pAllocatorPool;
    if (pool == nullptr) {
        pool = &g_defaultPool;
    }

    // Allocate a new 12-byte node
    ListNode* newNode = (ListNode*)(g_pAllocatorFunc)(0xC, pool);
    if (newNode) {
        // Store the caller's return address (or some value) at offset 0
        newNode->value = (void*) __builtin_return_address(0);
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }

    if (currentNode == g_pListHead) {
        // Insert at head: new node becomes head
        newNode->next = nullptr;
        g_pListHead = newNode;
    }
    else {
        // Insert after currentNode
        newNode->next = currentNode->next;
        if (currentNode->next) {
            currentNode->next->prev = newNode;
        }
    }

    newNode->prev = currentNode;
    currentNode->next = newNode;

    g_listCount++;

    // Store the new node address into output handle
    outHandle = newNode;
    return &outHandle;
}