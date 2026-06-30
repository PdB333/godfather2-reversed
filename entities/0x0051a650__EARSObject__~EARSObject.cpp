// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(void)
{
    int *piVar1;               // temporary pointer for list operations
    int iVar2;                 // temp node pointer
    int *piVar3;               // temp node pointer
    int *piVar4;               // temp node pointer
    undefined4 *puVar5;        // iterator for child list
    undefined4 *puVar6;        // next child node

    // --- Remove from first linked list (intrusive list with pointer at +0x31) ---
    // The object has a first intrusive list node pointer at offset +0x31 (196 bytes).
    // The node's 'next' field (at offset +4) points back to the storage location of this pointer.
    piVar1 = (int *)(this + 0x31);            // +0x31: first list node pointer location
    this->vtable = &PTR_FUN_00e3825c;         // set vtable to first (base) destructor level
    iVar2 = *piVar1;                          // fetch pointer to the actual node
    if (iVar2 != 0) {
        piVar3 = *(int **)(iVar2 + 4);        // node->next (points to piVar1 if sole node)
        if (piVar3 == piVar1) {
            // Only node: update head (stored at +0x32) to the node's saved next
            // (the node's next is overwritten with the head's value)
            *(int *)(iVar2 + 4) = this[0x32]; // +0x32: head pointer of this list
        } else {
            // Find previous node by following next pointers until next points to piVar1
            piVar4 = (int *)piVar3[1];
            while (piVar4 != piVar1) {
                piVar3 = (int *)piVar3[1];
                piVar4 = (int *)piVar3[1];
            }
            // Previous node's next = list head (which will replace current node)
            piVar3[1] = this[0x32];           // +0x32: head of this list
        }
    }

    // --- Decrement reference count on object pointed to by +0x08 ---
    // The pointer at +8 points to a ref-counted structure with count at +4.
    if (this[8] != 0) {
        piVar1 = (int *)(this[8] + 4);        // +4 relative to that object: refCount
        *piVar1 = *piVar1 - 1;                // decrement reference count
        if (*((int *)this[8] + 1) == 0) {     // if ref count became zero (field at +4)
            (**(code **)(*(int *)this[8] + 4))(); // call destructor on that object (vcall)
        }
        this[8] = 0;                          // clear the pointer
    }

    // --- Remove from second linked list (intrusive list at +0x06) ---
    // Similar pattern as above: pointer at +6, head at +7.
    iVar2 = this[6];                          // +0x06: second list node pointer
    if (iVar2 != 0) {
        puVar5 = *(undefined4 **)(iVar2 + 4); // node->next
        if (puVar5 == (undefined4 *)(this + 6)) {
            // Only node: update head at +0x07
            *(int *)(iVar2 + 4) = this[7];    // +0x07: head of second list
        } else {
            // Find previous node
            puVar6 = (undefined4 *)puVar5[1];
            while (puVar6 != (undefined4 *)(this + 6)) {
                puVar5 = (undefined4 *)puVar5[1];
                puVar6 = (undefined4 *)puVar5[1];
            }
            puVar5[1] = this[7];              // update previous node's next to head
        }
    }

    // --- Vtable update to second base class level ---
    this->vtable = &PTR_FUN_00e38258;

    // --- Clear a pointer at +0x02 ---
    // The object at +2 holds a pointer to something that gets zeroed.
    if (this[2] != 0) {
        *(int *)this[2] = 0;                  // zero out the pointed-to value
        this[2] = 0;                          // clear the pointer itself
    }

    // --- Final vtable update to most derived level ---
    this->vtable = &PTR_FUN_00e32808;

    // --- Walk singly linked list starting at +0x01 and clear each node ---
    // This appears to be a list of child objects or similar.
    puVar5 = (undefined4 *)this[1];           // +0x01: head of child list
    while (puVar5 != (undefined4 *)0) {
        puVar6 = (undefined4 *)puVar5[1];     // next node in list
        puVar5[1] = 0;                        // clear next pointer
        *puVar5 = 0;                          // clear first pointer (vtable?)
        puVar5 = puVar6;
    }
}