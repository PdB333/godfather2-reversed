// FUNC_NAME: PendingActionList::processAndClear
// Function at 0x006f9c90:
// Iterates over a linked list of pending action nodes, invokes a callback on each,
// optionally releases a resource, and notifies a manager. Clears the list at the end.

struct PendingActionNode {
    void* objectPtr;                 // +0x00: pointer to the actual object (often 'this')
    // +0x04..+0x08: (unknown, possibly padding or other data)
    void (*callback)(void*);         // +0x0C: function to call with objectPtr (e.g., a destructor)
    void* resourceToRelease;         // +0x10: secondary resource to free (if non‑null)
    PendingActionNode* next;         // +0x18: next node in the linked list
};

// The manager object contains a vtable; at offset 4 of that vtable is a notification
// function that accepts a node pointer and an int (0).
struct PendingListManager {
    void** vtable;                   // +0x00: pointer to vtable
};

// External function to release a resource (from Ghidra: FUN_004daf90)
extern void releaseResource(void* resource);

// __fastcall convention: 'this' is passed in ecx, uses param_1 as this pointer.
void __fastcall PendingActionList::processAndClear(PendingActionList* this) {
    PendingActionNode* node = this->head;          // *param_1
    while (node != nullptr) {
        // Save next pointer before any processing
        this->current = node->next;                // param_1[1] = piVar2[6]

        // Release an optional secondary resource
        if (node->resourceToRelease != nullptr) {  // if (piVar2[4] != 0)
            releaseResource(node->resourceToRelease);
        }

        // Invoke the object’s callback if the object pointer is valid
        if (node->objectPtr != nullptr) {          // if (*piVar2 != 0)
            node->callback(node->objectPtr);       // (*(code *)piVar2[3])(*piVar2)
        }

        // Notify the manager about this node
        // The notification function is at vtable offset 4 of the manager object
        // It is called with the node as the first argument and 0 as the second.
        void** vtable = this->manager->vtable;     // *(int *)param_1[4]
        void (*notify)(void*, int) = (void (*)(void*, int))vtable[1]; // +4 from vtable
        notify(node, 0);                           // (**(code **)(vtable+4))(node,0)

        // Advance to the next node
        node = this->current;                      // iVar1 = param_1[1]
        this->head = node;                         // *param_1 = iVar1
    }

    // Clear all list pointers
    this->head    = nullptr;                       // *param_1 = 0
    this->current = nullptr;                       // param_1[1] = 0
    this->someCount = 0;                           // param_1[2] = 0
}