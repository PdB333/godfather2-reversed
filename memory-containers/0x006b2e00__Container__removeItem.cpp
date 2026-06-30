// FUNC_NAME: Container::removeItem
void __thiscall Container::removeItem(int this, int itemId)
{
    uint count = *(uint *)(this + 0xb8); // +0xb8: number of items in array
    uint index = 0; // current search index

    if (count != 0) {
        int *arrayPtr = *(int **)(this + 0xb4); // +0xb4: pointer to dynamic array of int IDs
        do {
            if (*arrayPtr == itemId) { // found match
                if (-1 < (int)index) { // always true since index is unsigned, but original check keeps logic
                    if (index != count - 1) { // if not the last element
                        // shift last element into the removed slot
                        *(int *)(*(int *)(this + 0xb4) + index * 4) =
                            *(int *)(*(int *)(this + 0xb4) + (count - 1) * 4);
                    }
                    // decrement count
                    *(int *)(this + 0xb8) = count - 1;
                    // free/cleanup? (pass 0 meaning no immediate deallocation)
                    FUN_00790110(0);
                    // re-sort or compact the array
                    FUN_00791350(this);
                    return;
                }
                break; // not reached, but included for completeness
            }
            index++;
            arrayPtr++;
        } while (index < count);
    }

    // item not found in array
    if (*(int *)(this + 0xfc) == 0) { // +0xfc: flag indicating whether to allow pending add
        int pendingAllowed = FUN_007915b0(); // check if global pending list is ready
        if (pendingAllowed != 0) {
            FUN_008c2ab0(this, itemId); // add to pending removal list
        }
    }
    return;
}