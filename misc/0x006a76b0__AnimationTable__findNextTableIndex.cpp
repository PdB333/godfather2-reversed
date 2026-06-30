// FUNC_NAME: AnimationTable::findNextTableIndex
uint __thiscall AnimationTable::findNextTableIndex(SearchContext* ctx) {
    uint resultIndex = 0;
    uint count = *(int*)((uint)ctx + 4) + 2; // +0x4: base count
    uint maxCount = *(uint*)((uint)ctx + 8); // +0x8: clamp limit
    if (maxCount < count) {
        count = maxCount;
    }
    uint currentIdx = s_currentIndex; // DAT_012054b4
    float searchValue = *(float*)((uint)ctx + 0xc); // +0xc: value to search for

    // Unrolled loop: process 4 entries at a time
    if (count > 3) {
        do {
            // Check entry at currentIdx
            if (searchValue <= s_table[s_tableMask & currentIdx]) {
                s_currentIndex = currentIdx + 1;
                return resultIndex;
            }
            s_currentIndex = currentIdx + 2;
            // Check entry at currentIdx+1
            if (searchValue <= s_table[s_tableMask & (currentIdx + 1)]) {
                return resultIndex + 1;
            }
            s_currentIndex = currentIdx + 3;
            // Check entry at currentIdx+2
            if (searchValue <= s_table[s_tableMask & (currentIdx + 2)]) {
                return resultIndex + 2;
            }
            currentIdx += 4;
            // Check entry at currentIdx (after increment)
            if (searchValue <= s_table[s_tableMask & s_currentIndex]) {
                s_currentIndex = currentIdx;
                return resultIndex + 3;
            }
            resultIndex += 4;
            s_currentIndex = currentIdx;
        } while (resultIndex < count - 3);
    }

    // Process remaining entries (0 to 3)
    if (resultIndex < count) {
        while (true) {
            uint maskedIdx = s_tableMask & s_currentIndex;
            s_currentIndex = s_currentIndex + 1;
            if (searchValue <= s_table[maskedIdx]) {
                break;
            }
            resultIndex++;
            if (resultIndex >= count) {
                return resultIndex;
            }
        }
    }
    return resultIndex;
}