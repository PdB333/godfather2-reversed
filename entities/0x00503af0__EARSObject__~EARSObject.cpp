// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject()
{
    // Set vtable to base class destructor vtable (first in chain)
    this->vtable = (void**)&VTABLE_BASE_DESTRUCTOR; // +0x00, PTR_FUN_00e37ea0

    // If child object pointer at +0x28 exists, set a flag at offset 0x10 of that object
    if (this->childObject) // +0x28
    {
        uint* flag = (uint*)((char*)this->childObject + 0x10);
        *flag |= 1; // Mark the child as destroyed or pending removal
    }

    // Switch vtable to full object destructor vtable (for most derived class)
    this->vtable = (void**)&VTABLE_FULL_DESTRUCTOR; // +0x00, PTR_FUN_00e37110

    // If this object is part of a global linked list (node at +0x10), remove it
    if (this->listNode) // +0x10
    {
        // Get the global list head pointer stored at DAT_01206880 + 0x14
        int** listHead = (int**)(DAT_01206880 + 0x14);
        // Insert a sentinel and then the node into the list (likely removal by marking)
        *listHead = (int*)&LIST_SENTINEL; // PTR_LAB_01123be8
        (*listHead)++;
        *listHead = this->listNode;
        (*listHead)++;
        // Clear the node pointers
        this->listNode = 0;
        this->listNode2 = 0; // +0x14
    }
}