// FUNC_NAME: SomeObject::scalarDeletingDestructor
// Address: 0x004f9500
// Role: Scalar deleting destructor that optionally unlits from a global intrusive list and frees memory (EARS engine pattern).
// Data members: [4] = offset 0x10 (some linked-list pointer), [5] = offset 0x14 (another pointer).
// Global: DAT_01206880 + 0x14 is the head of a singly-linked list of active objects (each node has a vtable-like first field).

SomeObject* __thiscall SomeObject::scalarDeletingDestructor(SomeObject* this, unsigned char deletingFlag)
{
    int oldNextPtr;      // param_1[4], likely "mNext" or "mListLink"
    int** listHead;      // pointer to the global list head's current insertion point

    // Set vtable to a base/destructor version
    this->vtable = &PTR_FUN_00e37110;

    // Attempt to relink if the forward pointer is non-null
    oldNextPtr = this->field_10;           // offset 0x10
    if (oldNextPtr != 0) {
        // Access global list head (offset 0x14 from a global data block)
        listHead = (int**)(DAT_01206880 + 0x14);
        // Insert this node into the list: set the previous node's "next" to a stub vtable,
        // then store the old next pointer into the new node's vtable slot? (intrusive list using vtable as link)
        *(void***)*listHead = &PTR_LAB_01123be8;   // write a sentinel vtable into the head's first field
        *listHead = *listHead + 4;                  // advance to next field in the head node
        *(int*)*listHead = oldNextPtr;               // store the object's old next pointer into the head's new slot
        *listHead = *listHead + 4;                  // advance again
        // Clear the object's own linkage
        this->field_10 = 0;
        this->field_14 = 0;
    }

    // Conditional memory free (scalar deleting destructor pattern)
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this);   // likely operator delete or final destructor
    }

    return this;
}