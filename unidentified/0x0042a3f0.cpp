// ObjectListIterator::selectItem (0x0042a3f0)
// Sets the current item index and fills an output structure with a pointer to the item data, its ID, and a flag.
// The output pointer (outInfo) is passed via EDI in the original assembly; here provided as a parameter for clarity.
void __thiscall ObjectListIterator::selectItem(int index, int* outInfo)
{
    int currentIndex = *(int*)((char*)this + 0x20); // +0x20: currently selected index
    char hasNext = *(char*)((char*)this + 0x19);     // +0x19: flag indicating further items exist

    // First‑time initialization
    if (*(char*)((char*)this + 0x18) == 0) // +0x18: ‘iterator active’ flag
    {
        // If there is a previous selection, clean it up
        if (*(char*)((char*)this + 0x3c) != 0) // +0x3c: ‘needs release’ flag
        {
            releaseCurrentSelection(this); // FUN_004c4f50
        }
        hasNext = 0;
        *(char*)((char*)this + 0x18) = 1; // mark iterator as active
    }

    resetIterator(this); // FUN_004c52d0 – prepare internal cursor

    // If the index changed or no item was selected, update the current selection
    if ((hasNext == 0) || (index != currentIndex))
    {
        setActiveIndex(index); // FUN_004c4fb0 – points the internal cursor to the specified item
        *(char*)((char*)this + 0x19) = 1; // indicate that a valid item exists
        *(int*)((char*)this + 0x20) = index; // store new current index
    }

    short itemCount = *(short*)((char*)this + 0x1a); // +0x1a: number of items in the list (or a related short)
    // Default output (null pointer, invalid ID, no flag)
    outInfo[0] = 0;
    outInfo[1] = -1;
    outInfo[2] = -1;

    if (itemCount == 0)
    {
        return; // no items available
    }

    // Get the ID of the currently selected item from the internal cursor
    // +0x1c: pointer to a pointer to a ushort (the current item’s ID)
    unsigned short itemId = **(unsigned short**)((char*)this + 0x1c);
    // Compute the pointer to the item data:
    //   base (at +0x10) + itemId * elementSize (0x20)
    outInfo[0] = (int)itemId * 0x20 + *(int*)((char*)this + 0x10);
    outInfo[1] = (int)itemId;          // store the ID
    outInfo[2] = 0;                     // additional flag (unused)
}