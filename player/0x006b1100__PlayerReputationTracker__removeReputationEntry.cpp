// FUNC_NAME: PlayerReputationTracker::removeReputationEntry
// Address: 0x006b1100
// Removes a reputation entry from the sorted array and decrements the corresponding category counter.

void __thiscall PlayerReputationTracker::removeReputationEntry(int this, int entryInfo)
{
    // entryInfo structure:
    // +0x38: key (uint)
    // +0xc4: categoryIndex (uint, 0-9)
    
    // this structure:
    // +0x34: m_pReputations (pointer to array of ReputationRecord, 8 bytes each: uint key, uint value)
    // +0x38: m_numReputations (uint)
    // +0x40: m_categoryCounts[10] (int array)

    int *categoryCounts; // pointer to category counts array at this+0x40
    uint categoryIndex; // from entryInfo+0xc4
    uint key; // from entryInfo+0x38
    uint numReputations; // from this+0x38
    int *pRecord; // pointer to current record
    uint low, high, mid, temp; // binary search variables
    uint *recordKey;

    categoryIndex = *(uint *)(entryInfo + 0xc4);
    if (categoryIndex < 10) {
        // decrement the category counter
        categoryCounts = (int *)(this + 0x40);
        categoryCounts[categoryIndex] = categoryCounts[categoryIndex] - 1;
    }

    numReputations = *(uint *)(this + 0x38);
    if (numReputations == 0) {
        return;
    }

    key = *(uint *)(entryInfo + 0x38);
    low = 0xFFFFFFFF; // -1 as unsigned
    high = numReputations;

    // binary search for the record with matching key
    do {
        mid = (high + low) >> 1;
        temp = mid;
        recordKey = (uint *)(*(int *)(this + 0x34) + mid * 8);
        if (*recordKey < key) {
            temp = high; // set temp to current high
            low = mid;   // move low to mid
        } else {
            high = temp; // move high to mid
        }
        // Note: temp holds the new high value when key > recordKey, otherwise holds mid for high assignment
    } while (low + 1 != temp); // loop until adjacent

    // after loop, temp is the final high index
    if ((temp < numReputations) && (*(uint *)(*(int *)(this + 0x34) + temp * 8) == key) && ((int)temp >= 0)) {
        // found the record to remove; shift subsequent records left by one
        if (temp < numReputations - 1) {
            do {
                pRecord = (int *)(*(int *)(this + 0x34) + temp * 8);
                *pRecord = *(int *)(*(int *)(this + 0x34) + 8 + temp * 8); // copy key
                pRecord[1] = pRecord[3]; // copy value
                temp = temp + 1;
            } while (temp < *(int *)(this + 0x38) - 1);
        }
        // decrement record count
        *(int *)(this + 0x38) = *(int *)(this + 0x38) - 1;
    }
}