// FUNC_NAME: DataTable::getFloat
// 0x006259b0: DataTable::getFloat - Retrieves a float value associated with an integer key from a key-value table.
// Structure: this +0x08 = end pointer (sentinel), +0x0C = start of entries array.
// Each entry is 8 bytes: [type (int), value (float/int)].

float DataTable::getFloat(int key) {
    int* entryPtr;

    if (key < 1) {
        // For keys < 1, get the table's head/sentinel entry
        entryPtr = reinterpret_cast<int*>(DataTable::getFirstEntry()); // FUN_00625430
    } else {
        // Compute entry pointer from key (entry size = 8 bytes, offset = -8 + key*8)
        entryPtr = reinterpret_cast<int*>(
            *reinterpret_cast<int*>(this + 0x0C) + -8 + key * 8
        );
        // Bounds check: make sure entryPtr is within the table (start <= entryPtr < end)
        if (entryPtr >= *reinterpret_cast<int**>(this + 0x08)) {
            return 0.0f;
        }
    }

    if (entryPtr == nullptr) {
        return 0.0f;
    }

    int type = entryPtr[0]; // +0x00: type field
    if (type == 3) {
        // Type 3: value is stored directly as a float.
        return static_cast<float>(entryPtr[1]); // +0x04: float value
    }

    if (type == 4) {
        // Type 4: value is an integer index that requires resolution.
        // cloneKey is used to hold the resolved key (passed by address to resolve function)
        int resolvedKey = key;
        int localTemp = 0; // dummy local stack variable for aliasing
        bool resolved = DataTable::resolveKey(&resolvedKey); // FUN_00636850
        if (resolved) {
            // Abuse stack layout: localTemp is at lower address, resolvedKey at higher.
            // Returning (float)localTemp[1] actually returns (float)resolvedKey.
            // Use pointer arithmetic to align.
            entryPtr = &localTemp;
            // Fall through to return entryPtr[1] as float (which is resolvedKey now)
            return static_cast<float>(entryPtr[1]);
        }
    }

    return 0.0f;
}