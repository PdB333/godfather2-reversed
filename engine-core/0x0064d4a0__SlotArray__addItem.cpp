// FUNC_NAME: SlotArray::addItem

void __thiscall SlotArray::addItem(SlotArray* this, void* item)
{
    // this points to the array manager (in_EAX)
    // item is the object to add (param_1)
    // Object has an index field at offset +0x2c (int mIndex)
    // Array manager has:
    //   +0x1fc: pointer to array of object pointers (mArray)
    //   +0x200: current count (mCount)
    //   +0x204: capacity? (not used here)

    int* itemIndex = (int*)((char*)item + 0x2c);
    int* countPtr = (int*)((char*)this + 0x200);
    int* arrayBasePtr = (int*)((char*)this + 0x1fc);

    int count = *countPtr;
    if (*itemIndex != count)
    {
        // Swap the item with the last element (at position count)
        // The last element's index is updated to item's old index
        // This keeps the array compact with no gaps.
        int lastIndex = count;
        int oldItemIndex = *itemIndex;

        // Get pointer to the array of object pointers
        void** array = *(void***)((char*)this + 0x1fc);

        // Last element in array
        void* lastItem = array[lastIndex];
        int* lastItemIndex = (int*)((char*)lastItem + 0x2c);
        *lastItemIndex = oldItemIndex;  // Move last item to item's old slot

        // Copy the last element's pointer into item's old slot
        array[oldItemIndex] = array[lastIndex];

        // Place the new item at the last slot
        array[lastIndex] = item;

        // Update the item's index to the last slot
        *itemIndex = lastIndex;
    }

    // Increment count
    (*countPtr)++;
}