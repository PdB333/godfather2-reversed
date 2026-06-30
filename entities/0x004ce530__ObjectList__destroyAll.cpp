// FUNC_NAME: ObjectList::destroyAll
void __fastcall ObjectList::destroyAll(int this) // this in ecx
{
    // this+0x24: pointer to dummy list head (intrusive doubly-linked list)
    // this+0x28: count of nodes (reset to 0)
    // this+0x2c: some internal counter (decremented for each freed node)
    // this+0x0c: pointer to allocator or node deletion vtable

    int *piVar1;          // pointer to data object stored in a list node
    int iVar2;            // temporary for counter adjustment
    int *piVar3;          // temporary for traversing remaining nodes

    // Traverse the list starting from the first real node (next of dummy head)
    // The dummy head is a sentinel; the list circularly wraps around to it.
    // Node layout: [0] next, [4] prev, [8] dataObject*
    for (undefined4 *nodePtr = **(undefined4 ***)(this + 0x24);
         nodePtr != *(undefined4 **)(this + 0x24);
         nodePtr = (undefined4 *)*nodePtr)
    {
        if (nodePtr == *(undefined4 **)(this + 0x24))
        {
            // Safety assertion – should never reach dummy head in loop
            FUN_00b97aea();
        }

        piVar1 = (int *)nodePtr[2]; // data object pointer at node offset 0x8

        // Destroy sub-object at dataObject + 0x20
        // FUN_004086d0 and FUN_00408310 likely destructors or cleanup
        FUN_004086d0(piVar1 + 8); // treats piVar1 as int*, so offset 0x20
        FUN_00408310(piVar1 + 8);

        // If dataObject[4] (offset 0x10) is non-null, call its virtual destructor
        // The function pointer is at dataObject[7] (offset 0x1c)
        if (piVar1[4] != 0)
        {
            (*(code *)piVar1[7])(piVar1[4]);
        }

        // If dataObject[0] (offset 0x00) is non-null, call a virtual function on it
        // The function pointer is at dataObject[3] (offset 0x0c)
        if (*piVar1 != 0)
        {
            (*(code *)piVar1[3])(*piVar1);
        }

        iVar2 = *(int *)(this + 0x2c); // some counter from this

        // Free the data object using a global deallocation function
        (*DAT_012059e0)(piVar1);

        // If the internal counter was non-zero, decrement a nested count
        // (pointer arithmetic: base+0x10 -> field, then +0x24 -> count, subtract 0x28)
        if (iVar2 != 0)
        {
            piVar1 = (int *)(*(int *)(iVar2 + 0x10) + 0x24);
            *piVar1 = *piVar1 + -0x28;
        }

        if (nodePtr == *(undefined4 **)(this + 0x24))
        {
            FUN_00b97aea(); // re-check safety
        }
    }

    // Reset the list: make dummy head point to itself, count = 0
    piVar1 = *(int **)(this + 0x24);        // pointer to head
    piVar3 = (int *)*piVar1;                // save first real node (if any)
    *piVar1 = (int)piVar1;                  // head->next = head
    *(int *)(*(int *)(this + 0x24) + 4) = *(int *)(this + 0x24); // head->prev = head
    *(undefined4 *)(this + 0x28) = 0;       // node count = 0

    // Delete any remaining nodes that were not freed in the first loop
    // (this happens if the list was non-empty, as the loop above stops when
    //  it would wrap back to head, but doesn't free the nodes themselves)
    if (piVar3 != *(int **)(this + 0x24))
    {
        do
        {
            piVar1 = (int *)*piVar3; // next node
            // Call node destructor through vtable at (this+0xc)->vtable[4]
            (**(code **)(**(int **)(this + 0xc) + 4))(piVar3, 0xc);
            piVar3 = piVar1;
        } while (piVar1 != (int *)*(int *)(this + 0x24));
    }

    return;
}