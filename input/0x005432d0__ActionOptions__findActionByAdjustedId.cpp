// FUNC_NAME: ActionOptions::findActionByAdjustedId
uint ActionOptions::findActionByAdjustedId(uint adjustedId, uint contextParam) {
    uint idx = 0;
    if (this->entryCount != 0) {
        int* entries = reinterpret_cast<int*>(this->entriesPtr); // +0x2B8: pointer to array of [key, value] pairs
        do {
            int raw = *entries;
            uint key = (raw == 0) ? 0 : static_cast<uint>(raw - 0x48); // stored keys are offset by 0x48
            if (key == adjustedId) {
                // Call virtual function at vtable offset 0x218 (slot 0x86)
                // The function takes the entry index and contextParam, returns a result
                idx = (this->*reinterpret_cast<uint(ActionOptions::*)(uint,uint)>(
                    *reinterpret_cast<void**>(reinterpret_cast<uint*>(this)[0] + 0x218)
                ))(idx, contextParam);
                return idx;
            }
            idx++;
            entries += 2; // skip the second int of the pair (unused here)
        } while (idx < this->entryCount);
    }
    // No match found; original code returns (lastKey & 0xFFFFFF00), likely an error code
    // Simplified as 0 for clarity
    return 0;
}