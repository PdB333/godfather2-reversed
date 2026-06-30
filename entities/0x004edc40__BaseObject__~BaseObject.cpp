// FUNC_NAME: BaseObject::~BaseObject
// Address: 0x004edc40
// Destructor for a base EARS object. Removes the object from its linked list
// (or returns its node to a global free list) and optionally deallocates memory.
// param_1: this pointer
// param_2: flags (bit 0 indicates if memory should be freed)

undefined4 * __thiscall BaseObject::~BaseObject(undefined4 *this, byte flags)
{
    int nodePtr;
    int *freeListPtr;

    // Set vtable to a null/base vtable (prevents virtual calls during/after destruction)
    *this = &PTR_FUN_00e37110;

    nodePtr = this[4]; // +0x10: next pointer in node list (or to a node structure)
    if (nodePtr != 0) {
        // Global pool manager at DAT_01206880: offset 0x14 holds a free list pointer
        freeListPtr = (int *)(DAT_01206880 + 0x14);

        // Insert the node into the free list: write sentinel at current free list head,
        // then store node pointer, then advance head by two slots (marker + pointer)
        *(void ***)*freeListPtr = &PTR_LAB_01123be8; // write marker sentinel
        *freeListPtr = *freeListPtr + 4;             // advance past marker
        *(int *)*freeListPtr = nodePtr;              // store node pointer
        *freeListPtr = *freeListPtr + 4;             // advance past pointer

        // Clear the local node pointers (next/prev)
        this[4] = 0; // +0x10
        this[5] = 0; // +0x14
    }

    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete or custom deallocation
    }

    return this;
}