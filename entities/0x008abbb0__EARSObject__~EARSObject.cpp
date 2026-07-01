// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x008abbb0
// Role: Destructor for base EARS object with intrusive linked list removal and optional memory deallocation.
// Offsets:
//   +0x28: vtable pointer for first base (set to VTABLE_BASE1)
//   +0x38: vtable pointer for second base (set to VTABLE_BASE2)
//   +0x18: pPrevNode - pointer to previous node in a doubly-linked list
//   +0x1c: pNextNode - pointer to next node in a doubly-linked list
//   +0x20: pListHead - pointer to the list's head/sentinel (or other link data)
// The removal logic updates adjacent node pointers using offsets 4 and 8 from those nodes,
// likely matching a known intrusive list node structure (e.g., offset 4 = next, offset 8 = prev).

int __thiscall EARSObject::~EARSObject(EARSObject* this, byte shouldDelete)
{
    // Call base class destructor (likely a virtual base or framework class)
    FUN_004bc3f0();

    // Restore vtable pointers to base class tables (ensuring proper virtual dispatch)
    *(void***)(this + 0x38) = &PTR_LAB_00e35c24;   // Second vtable restored
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;   // First vtable restored

    // Remove this node from a doubly-linked list.
    // The node stores three pointers: pPrevNode (offset 0x18), pNextNode (offset 0x1c),
    // and a third pointer (offset 0x20) that might be a list-head or sentinel.
    int* pPrev = *(int**)(this + 0x18);
    int* pNext = *(int**)(this + 0x1c);
    int* pListData = *(int**)(this + 0x20);

    if (pPrev != NULL) {
        if (pNext == NULL) {
            // If no next node, update previous node's 'next' field (at +4) to point to list data
            *(int**)(pPrev + 4) = pListData;
        } else {
            // Otherwise, update next node's 'prev' field (at +8) to point to list data
            *(int**)(pNext + 8) = pListData;
        }
        if (pListData != NULL) {
            // Update the list data's 'next' field (at +4) to point to the next node
            *(int**)(pListData + 4) = pNext;
        }
    }

    // Additional cleanup (likely calls destructor of another base or clears resources)
    FUN_0064d150();

    // If the 'shouldDelete' flag (bit 0) is set, deallocate the object's memory via operator delete
    if ((shouldDelete & 1) != 0) {
        FUN_009c8eb0(this);   // operator delete(this)
    }

    return (int)this;
}