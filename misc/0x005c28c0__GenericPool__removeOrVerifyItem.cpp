// FUNC_NAME: GenericPool::removeOrVerifyItem
void __fastcall GenericPool::removeOrVerifyItem(int *pool) // ECX = pool base (this), EDX = itemPtr?
{
    int *currentItem = (int *)*pool;       // pool[0] = head of linked list (next item pointer)
    int *nextItem;
    int *itemParam;                        // param_1 = item to remove/verify (from EDX fastcall)
    int *edxBackup = (int *)unaff_EDI;     // preserves EDI (likely 'this' in caller)

    // First pass: find item by pointer identity
    nextItem = currentItem;
    while (nextItem != (int *)0x0) {
        if (nextItem == itemParam)
            goto found_item;
        nextItem = (int *)nextItem[4];     // +0x10 (offset 4 * 4) = next pointer in linked list
    }

    // Second pass: find item by value match (ID pair)
    if (currentItem != (int *)0x0) {
        nextItem = currentItem;
        do {
            if ((*itemParam == *nextItem) && (itemParam[1] == nextItem[1]))  // compare first two 32-bit fields
                goto found_item;
            nextItem = (int *)nextItem[4];  // +0x10 = next
        } while (nextItem != (int *)0x0);
    }

    goto skip_or_continue;

found_item:
    if (nextItem != (int *)0x0) {
        // Unlink item from list
        if ((int *)pool[1] == nextItem) {   // pool[1] = tail pointer (or free list head?)
            pool[1] = (int)nextItem[4];     // update tail to next
        }
        if (currentItem == nextItem) {
            *pool = (int)currentItem[4];    // update head to next
        }
        FUN_005c2e30();                     // pool->freeNode() or release node back to allocator
    }

skip_or_continue:
    // Ensure tail is initialized if empty
    if (pool[1] == 0) {
        pool[1] = *pool;                    // tail = head (list has one item or becomes circular)
    }
    return;
}