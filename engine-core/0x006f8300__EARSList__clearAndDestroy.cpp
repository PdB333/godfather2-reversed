// FUNC_NAME: EARSList::clearAndDestroy

void __thiscall EARSList::clearAndDestroy(int *this)
{
    int *node;         // current node pointer
    int *nextNode;     // next node pointer
    int *extraPtr;     // pointer at this+0xC

    node = (int *)*this;                     // this+0x00: head of list
    while (node != (int *)0) {
        nextNode = (int *)node[5];           // node+0x14: next pointer (5 ints = 20 bytes offset)

        // Release first member at node+0xC (offset 12)
        if (node[3] != 0) {                  // node+0x0C
            FUN_004daf90(node + 3);          // assumes node+0xC is an object to free
        }
        // Release second member at node+0x4 (offset 4)
        if (node[1] != 0) {                  // node+0x04
            FUN_004daf90(node + 1);          // free node+0x04
        }

        // Call vtable method 1 (offset 0x4) on node with flag 0
        // vtable[1] takes (object*, int) — possibly destroy/delete node
        ((void (__fastcall *)(int *, int))this[4][1])(node, 0);  // this[4] = vtable at offset 0x10

        node = nextNode;
    }

    // After list iteration, handle extra pointer at this+0xC
    extraPtr = (int *)this[3];               // this+0x0C
    if (extraPtr != (int *)0) {
        ((void (__fastcall *)(int *, int))this[4][1])(extraPtr, 0);
    }

    // Finally, call vtable method 3 (offset 0xC) to destroy the container itself
    ((void (*)())this[4][3])();              // vtable[3] takes no arguments
}