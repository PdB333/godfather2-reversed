// FUNC_NAME: List_PushFront

// Push an object pointer with embedded reference count onto a singly-linked list.
// The list's head is stored in the global g_pListHead.
// The object must have an int reference count at offset 0 (e.g., class Derived : public RefCountBase).
// Allocates a ListNode from a custom allocator (g_allocator). On failure, the current list
// is moved to a dangling pointer and the list is cleared.
void List_PushFront(int** ppObject)  // ppObject points to a pointer to an object with refcount at +0x0
{
    // Custom memory allocator: (void*)(*DAT_0119caf0)(uint size, uint flags)
    // Returns 8-byte aligned memory; may fail (returns nullptr).
    typedef void* (*AllocFn)(unsigned int size, unsigned int flags);
    static AllocFn g_allocator = (AllocFn)(*DAT_0119caf0);

    // Head of the linked list (stored in ESI register at entry, assumed static)
    static ListNode* g_pListHead; // originally unaff_ESI

    // Dangling pointer used when allocation fails (global DAT_00000004)
    static ListNode* g_pListDanglingHead;

    struct ListNode {
        int* pObject;      // +0x00: pointer to the referenced object
        ListNode* pNext;   // +0x04: next node in list
    };

    ListNode* pNewNode = (ListNode*)g_allocator(8, 0);
    if (pNewNode != nullptr)
    {
        int* pObject = *ppObject;
        pNewNode->pObject = pObject;
        if (pObject != nullptr)
        {
            // Increment the reference count at offset 0 of the object
            (*pObject)++;  // equivalent to (*(int*)pObject)++
        }
        pNewNode->pNext = nullptr;
        pNewNode->pNext = g_pListHead;   // link to current head
        g_pListHead = pNewNode;          // make new node the head
        return;
    }
    // Out of memory: save current list into dangling pointer, then clear head
    g_pListDanglingHead = g_pListHead;
    g_pListHead = nullptr;
    return;
}