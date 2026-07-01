// FUNC_NAME: PointerArray::clearAndDestroy
void __thiscall PointerArray::clearAndDestroy(PointerArray* thisPtr)
{
    // +0x00: void** items (pointer to array of pointers)
    // +0x04: int count (number of elements)
    // +0x08: int capacity (not used in loop, but reset at end)
    int idx = thisPtr->count;
    while (--idx >= 0)
    {
        void* item = thisPtr->items[idx];
        if (item != nullptr)
        {
            // Release/destroy the item (FUN_004daf90)
            releaseItem(item);
        }
    }
    thisPtr->count = 0;
    // Free the underlying array (FUN_009c8f10)
    deallocate(thisPtr->items);
    thisPtr->items = nullptr;
    thisPtr->capacity = 0;
}