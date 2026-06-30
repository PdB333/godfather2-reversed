// FUNC_NAME: FixedSizeArray::iterate
// Address: 0x006f5e20
// Role: Advance an iterator through a fixed-size array of 0x24-byte items.
// The iterator state is stored in the int pointed to by ppCurrentItem.
// When *ppCurrentItem is 0, it initializes to the first item.
// Returns true if a next item exists, false if end of array (or invalid).

bool FixedSizeArray::iterate(int *ppCurrentItem)
{
    // +0x0c: pointer to array descriptor
    ArrayDescriptor *pDesc = *(ArrayDescriptor **)(this + 0x0c);
    if (pDesc == nullptr)
        return false;

    // pDesc layout:
    // +0x00: unknown (maybe padding or other data)
    // +0x02: ushort count
    // +0x04: pointer to first item (each item is 0x24 bytes)
    ushort count = *(ushort *)(pDesc + 0x02);
    void *pFirst = *(void **)(pDesc + 0x04);
    if (pFirst == nullptr || count == 0)
        return false;

    int current = *ppCurrentItem; // raw address stored as int
    if (current == 0)
    {
        // Start iteration: return first item
        *ppCurrentItem = (int)pFirst;
        return true;
    }
    else
    {
        // Compute index: (current - pFirst) / 0x24
        int index = (current - (int)pFirst) / 0x24;
        if (index >= 0 && index < (int)(count - 1))
        {
            // Advance to next item
            *ppCurrentItem = current + 0x24;
            return true;
        }
        else
        {
            // End of array: reset and signal failure
            *ppCurrentItem = 0;
            return false;
        }
    }
}