// FUNC_NAME: ArrayContainer::removeAtIndex
void __thiscall ArrayContainer::removeAtIndex(uint index)
{
    // This provides a fixed-size array of 12-byte elements (capacity 8? Based on count offset 0x60).
    // m_count is stored at this+0x60.
    uint count = *(uint *)(this + 0x60);
    if (index >= count)
        return;

    // If not removing the last element, shift elements after index left.
    if (index < count - 1)
    {
        // Shift the element at (count-1) to index? Actually call a helper that likely copies/moves.
        // The helper is called with pointer to the last element (this + (count-1)*12).
        FUN_0071da80(this - 0xc + count * 0xc); // this + (count-1)*0xc
    }

    // Decrement count.
    *(int *)(this + 0x60) = count - 1;

    // Get pointer to the now-vacant last slot (at new count index).
    int *lastSlot = (int *)(this + (count - 1) * 0xc);
    if (*lastSlot != 0)
    {
        // Clean up the old element (likely destructor or reference decrement).
        FUN_004daf90(lastSlot);
    }

    // Reset the slot to zero and assign a global default value to the third field.
    // DAT_00e44758 appears to be a sentinel or default for the third int.
    undefined4 *slot = (undefined4 *)(this + (count - 1) * 0xc);
    if (slot != (undefined4 *)0x0)
    {
        slot[0] = 0; // first int
        slot[1] = 0; // second int
        slot[2] = DAT_00e44758; // third int (global default)
    }
}