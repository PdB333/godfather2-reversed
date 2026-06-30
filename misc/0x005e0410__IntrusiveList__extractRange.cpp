// FUNC_NAME: IntrusiveList::extractRange
void IntrusiveList::extractRange(int* outPrevNext, void* param2, void* param3, void* param4, void* param5)
{
    // unaff_EDI is 'this' pointer (IntrusiveList*)
    // Structure layout:
    // this+0x1c: pointer to sentinel node (head of list)
    // this+0x20: count or flag (zeroed during reset)

    int* sentinel = *(int**)((char*)this + 0x1c); // sentinel node pointer
    int firstNode = *sentinel;                     // first actual node (if list non-empty)

    // Validate parameters: param2 and param4 should be 'this' or null
    if (param2 != nullptr && param2 != this) {
        FUN_00b97aea(); // assertion failure
    }

    if (param3 == (void*)firstNode) {
        int* sentinel2 = *(int**)((char*)this + 0x1c); // re-fetch (same)
        if (param4 != nullptr && param4 != this) {
            FUN_00b97aea(); // assertion failure
        }
        if (param5 == (void*)sentinel2) {
            // Special case: clear entire list (reset to empty)
            FUN_005e1400(sentinel2[1]);  // destroy first node? (node at sentinel+4)
            sentinel2[1] = (int)sentinel2; // sentinel->next = sentinel
            *(int*)((char*)this + 0x20) = 0; // count = 0
            sentinel2[0] = (int)sentinel2; // sentinel->prev = sentinel
            sentinel2[2] = (int)sentinel2; // sentinel+8 = sentinel (maybe third pointer)
            outPrevNext[1] = *sentinel2;   // first node (now sentinel itself)
            *outPrevNext = (int)this;
            return;
        }
    }

    // Generic case: iterate until param3 == param5 (range endpoints)
    while (true) {
        if (param2 != nullptr && param2 != param4) {
            FUN_00b97aea(); // assertion failure
        }
        if (param3 == param5) break; // range found
        FUN_005e15c0(); // advance iteration? (unclear)
        FUN_005e0c80(this, (undefined1*)&outPrevNext, param2, param3); // process node
    }

    // Return the range endpoints as output
    outPrevNext[1] = (int)param3; // end of range
    *outPrevNext = (int)param2;   // start of range
    return;
}