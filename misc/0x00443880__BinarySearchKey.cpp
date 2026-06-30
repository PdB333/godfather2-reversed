// FUNC_NAME: BinarySearchKey
int __thiscall BinarySearchKey(int* table, unsigned int* keyPtr)
{
    // table[0] = pointer to array of 8-byte entries (key at offset 0, value at offset 4)
    // table[1] = number of entries
    int count = table[1];
    int foundIndex = -1;
    int hi = count - 1;
    int lo = 0;

    if (count != 0)
    {
        int mid;
        int newLo;
        do
        {
            mid = lo + (hi - lo) / 2;
            // mid = lo + hi >> 1; // original: iVar3 = iVar4 + iVar6 >> 1; (but note operator precedence: >> binds lower than +, so it's (iVar4 + iVar6) >> 1)
            // Actually original code: iVar3 = iVar4 + iVar6 >> 1; This is ambiguous. In C, + and >>, + has higher precedence, so it's (iVar4 + iVar6) >> 1.
            // But typical binary search uses mid = (lo + hi) / 2. So we'll use that.
            newLo = mid;
            if (*(unsigned int*)(table[0] + mid * 8) < *keyPtr)
            {
                newLo = mid + 1; // original: iVar5 = iVar4; (which was lo?) then iVar6 = iVar3; Actually careful.
                // Let's re-express the original code properly.
                // Original loop:
                // iVar4 = iVar1; // lo = count? Wait, initially iVar4 = iVar1 (count). Actually iVar4 = iVar1 (count) and iVar6 = -1 (hi = -1). That's reversed.
                // Actually the code does: iVar4 = count; iVar6 = -1;
                // Then do { iVar3 = (iVar4 + iVar6) >> 1; iVar5 = iVar3; if (key < target) { iVar5 = iVar4; iVar6 = iVar3; } iVar4 = iVar5; } while (iVar6 + 1 != iVar5);
                // This is a tricky binary search where lo starts at count (invalid) and hi at -1. It's searching in [0, count-1].
                // After loop, if (iVar5 < count && array[iVar5] == key) return iVar5; else -1.
                // This is actually a standard lower_bound search. We'll implement it cleanly.
                // Let's rewrite using standard binary search for clarity.
            }
            // We'll just implement straightforward binary search.
        } while (0); // placeholder
    }

    // Better to rewrite from scratch with standard logic:
    int low = 0;
    int high = count - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        unsigned int entryKey = *(unsigned int*)(table[0] + mid * 8);
        if (entryKey < *keyPtr)
            low = mid + 1;
        else if (entryKey > *keyPtr)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}