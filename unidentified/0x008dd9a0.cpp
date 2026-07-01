// FUN_008dd9a0: GameApplication::destructor
// Destructor for a global manager object. Cleans up static sub-objects, releases a dynamic array,
// and resets vtable pointers. Called from vtable thunk at 0x008ddc30.

void __fastcall GameApplication::destructor(int *this)
{
    int *elemPtr;
    int elemCount;
    int idx;
    int *curElem;

    // Set up destructor vtables (self and members)
    this[0] = (int)&PTR_FUN_00d7e934;      // vtable pointer
    this[1] = (int)&PTR_LAB_00d7e924;      // secondary vtable
    this[4] = (int)&PTR_LAB_00d7e914;      // sub-vtable

    // Destroy static global sub-objects (order matches construction)
    subObject_destructor(&DAT_012069c4);    // static pool A cleanup
    subObject_destructor(&DAT_0112fc6c);    // static pool B cleanup
    subObject_destructor(this + 10);        // member sub-object destruction
    subObject_destructor(&DAT_0112fc60);    // static thread data cleanup
    subObject_destructor(&DAT_0112fc74);    // static allocator cleanup
    subObject_destructor(&DAT_0112fc7c);    // static memory tracker cleanup

    // Finalize string hashing (hash constant for "Destroy")
    hashString(0x9ab67f60);

    // Destroy dynamic array of elements (each element is 12 bytes = 3 ints)
    elemPtr = (int *)this[9];
    if (elemPtr != 0) {
        elemCount = *(int *)(elemPtr - 1); // element count stored before array
        for (idx = elemCount - 1; idx >= 0; idx--) {
            curElem = (int *)((char *)elemPtr + idx * 0xc);
            if (*curElem != 0) {
                destroyElement(curElem); // destroy each element (likely a small struct)
            }
        }
        deallocateArray((int *)((char *)elemPtr - 4)); // free array header
    }

    // Replace vtable with base destructor vtable
    this[4] = (int)&PTR_LAB_00e30fe0;
    globalCleanupSubsystem();             // finalize globals
    this[0] = (int)&PTR_LAB_00d7e8d0;    // reset vtable to base

    // Mark global singleton destroyed
    DAT_0112998c = 0;
}