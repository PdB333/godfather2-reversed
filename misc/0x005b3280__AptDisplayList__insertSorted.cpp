// FUNC_NAME: AptDisplayList::insertSorted
// Address: 0x005b3280
// Role: Inserts a display list item into a sorted array (descending order by sort key at +0x58).
// Array is at this+0x00 (32 slots), count at this+0x80.
// File: ..\source\Apt\AptDisplayList.cpp (line 0x266)

void AptDisplayList::insertSorted(void* pItem)
{
    int count = *(int*)((char*)this + 0x80); // +0x80: m_count
    int insertIdx = 0;

    // Find insertion point: descending order based on value at +0x58 of each item
    while (insertIdx < count)
    {
        void* existing = *(void**)((char*)this + insertIdx * 4); // m_items[insertIdx]
        int existingKey = **(int**)((char*)existing + 0x58); // item->sortKey
        int newKey = **(int**)((char*)pItem + 0x58);         // pItem->sortKey
        if (existingKey < newKey)
            break;
        insertIdx++;
    }

    // Debug assertion: array capacity is 32 (aMasks size)
    if (insertIdx >= 32)
    {
        // Assertion: "i < ((int)(sizeof(aMasks) / sizeof(aMasks[0])))"
        // In debug builds, this triggers a breakpoint; in release, it's a no-op.
        // For safety, we return early.
        return;
    }

    // Shift elements to make room for the new item
    if (insertIdx < count)
    {
        for (int i = count; i > insertIdx; i--)
        {
            *(void**)((char*)this + i * 4) = *(void**)((char*)this + (i - 1) * 4);
        }
    }

    // Insert the new item
    *(void**)((char*)this + insertIdx * 4) = pItem;

    // Increment count
    *(int*)((char*)this + 0x80) = count + 1;
}