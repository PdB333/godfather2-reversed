// FUNC_NAME: Destructible::~Destructible
void __thiscall Destructible::~Destructible()
{
    // +0x00: vtable pointer
    // +0x14: sub-object pointer (or function pointer set to base vtable)
    // +0x17: another pointer set to base label
    // +0x18: next pointer in linked list
    // +0x19: pointer to previous node's 'next' field (for linked list removal)
    // +0x1a: pointer to a linked object (e.g., SimObject with large offset structure)
    // +0x1e: bitfield flags

    int* linkedObj = this->linkedObject; // +0x1a
    *this = &PTR_LAB_00d76eb4;           // Replace vtable with base class vtable
    this->subObjectPtr = &PTR_FUN_00d76ea0; // +0x14: set sub-object vtable
    this->someOtherPtr = &PTR_LAB_00d76e9c; // +0x17: another vtable/data pointer

    // Check if linkedObj has bit 1 set (0x2) in its state flags at +0xc88
    if ((*(uint*)(linkedObj + 0xc88) & 0xfffffffd) != *(uint*)(linkedObj + 0xc88))
    {
        // Clear bit 1 and call a virtual function on linkedObj (argument 0x10)
        (**(code**)(*(int*)(linkedObj + 0x58) + 0x28))(0x10);
        *(uint*)(linkedObj + 0xc88) &= 0xfffffffd; // Clear bit 1
    }

    // If linkedObj is valid, check a global system (DAT_01131018) and destruct sub-object at +0x14
    if (this->linkedObject != 0)
    {
        int globalSystemValid = isPointerValid(DAT_01131018); // FUN_0043b870
        if (globalSystemValid != 0)
        {
            destructSubObject(this + 0x14); // FUN_009af0a0 – destruct the sub-object
        }
    }

    // Synchronize flag bit 2: if this->flags has bit 2 set but linkedObj's flags do not
    if ((this->flags >> 2 & 1) != 0 && ((*(uint*)(this->linkedObject + 0xc88) >> 2 & 1) == 0))
    {
        clearFlag(2); // FUN_00544ae0 – likely clears a global or system flag
    }

    // If this->flags has bit 3 set and linkedObj is valid, remove this node from a doubly linked list
    if ((this->flags >> 3 & 1) != 0 && this->linkedObject != 0)
    {
        // +0x19: pointer to previous node's 'next' field
        int* prevNextPtr = (int*)this->prevPtr;
        // +0x18: next node pointer
        int nextNode = this->nextPtr;
        *prevNextPtr = nextNode;                           // prev->next = next
        *(int**)(nextNode + 4) = prevNextPtr;              // next->prev = &(prev->next) [or prev field]
    }

    globalCleanup(); // FUN_004ac1e0 – final cleanup or memory release
    return;
}