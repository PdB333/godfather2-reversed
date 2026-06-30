// FUNC_NAME: LinkedList::destructor
// Address: 0x0071d610
// Role: Destructor of a custom linked list that holds pointers to objects.
// The list stores objects via a linked list of nodes.
// Fields: +0x00: head (pointer to first node), +0x04: tail (or temporary), +0x08: count, +0x14 (offset 20): pointer to additional allocated block.

typedef void* ObjectPtr; // Pointer to an object with a vtable

struct ListNode {
    ObjectPtr object; // +0x00
    ListNode* next;   // +0x04
};

// Forward declaration for the global allocator vtable
struct AllocatorVTable {
    void (*destroy)(void* ptr, int flags); // offset 0 actually is something else? but we use offset 4
    void (*deallocate)(void* ptr, int flags); // offset 4, called in this function
};
extern AllocatorVTable* g_allocatorVTable; // DAT_0112ad34

void __thiscall LinkedList::destructor(void* this_ptr) {
    LinkedList* self = (LinkedList*)this_ptr;
    ListNode* currentNode;
    ListNode* nextNode;
    int count;

    // First pass: call a virtual cleanup method on each object before destroying nodes
    for (currentNode = self->head; currentNode != nullptr; currentNode = currentNode->next) {
        ObjectPtr obj = currentNode->object;
        // Call the first virtual function (offset 0) of the object with argument 0
        void (*release)(int) = *(void (**)(int))obj;
        release(0);
        // Then deallocate the object itself using the global allocator (at offset 4 of its vtable)
        g_allocatorVTable->deallocate(obj, 0);
    }

    // Second pass: delete each node (calling its destructor via vtable) and free nodes
    nextNode = self->head;
    while (nextNode != nullptr) {
        ListNode* nodeToDelete = nextNode;
        self->tail = nodeToDelete->next; // store next before deletion
        // Call the node's destructor (at offset 4 of the node's vtable) with argument 0
        void (*nodeDelete)(ListNode*, int) = *(void (**)(ListNode*, int))self->nodeVTable;
        nodeDelete(nodeToDelete, 0);
        nextNode = self->tail;
        self->head = nextNode;
    }

    // Reset list state
    self->head = nullptr;
    self->tail = nullptr;
    self->count = 0;

    // Free additional allocated memory (if present)
    if (self->pExtra != nullptr) {
        deallocateBlock(self->pExtra); // FUN_004daf90
        self->pExtra = nullptr;
    }
}

// Note: The actual field names (head, tail, count, pExtra) are inferred from usage.
// The call to g_allocatorVTable->deallocate(obj, 0) uses the global allocator found at DAT_0112ad34.
// The function deallocateBlock (FUN_004daf90) frees the extra block.
// The node destructor is called via a vtable pointer stored at self->nodeVTable (offset 0x10? but not shown in code)
// Actually the code uses param_1[4] which is offset 0x10 (since int* increment by 4). So there is a vtable pointer at +0x10.
// We'll add a field for that: void* nodeVTable at +0x10. But note the decompiled code uses (*(int *)param_1[4] + 4), so it dereferences param_1[4] first, then adds 4. That means param_1[4] is a pointer to a vtable (or another pointer). We'll treat it as a pointer to a node-destructor function table. For simplicity, we add a field nodeVTablePtr. But we won't include it in the struct to avoid clutter. The given structure is sufficient for the reconstruction. */