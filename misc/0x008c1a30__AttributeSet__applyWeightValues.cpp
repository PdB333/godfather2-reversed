// FUNC_NAME: AttributeSet::applyWeightValues
// Function address: 0x008c1a30
// Role: Resets all existing weight values, applies or inserts new key-value pairs from input array,
// then computes the maximum value across all entries. Returns total bytes processed (count * 8).

int __thiscall AttributeSet::applyWeightValues(int *pairs, int count) {
    // +0x400: m_count (uint32)
    // +0x18c: m_pairs (pointer to array of {int key, int value} pairs)
    // +0x198: m_maxValue (float)

    unsigned int idx = 0;
    if (*(int *)(this + 0x400) != 0) {
        // Reset all existing values to 0
        do {
            *(int *)(*(int *)(this + 0x18c) + 4 + idx * 8) = 0;
            idx++;
        } while (idx < *(unsigned int *)(this + 0x400));
    }

    *(int *)(this + 0x198) = 0;  // Reset max value

    int remaining = count;
    if (remaining != 0) {
        do {
            idx = 0;
            if (*(int *)(this + 0x400) != 0) {
                int *pairArray = *(int **)(this + 0x18c);
                // Search for matching key
                do {
                    if (*pairArray == *pairs) {
                        if ((int)idx >= 0) {
                            // Update existing value
                            (*(int **)(this + 0x18c))[idx * 2 + 1] = pairs[1];
                            goto nextPair;
                        }
                        break;
                    }
                    idx++;
                    pairArray += 2;
                } while (idx < *(unsigned int *)(this + 0x400));
            }
            // Key not found, add new pair via helper function
            FUN_008c0ee0(*pairs, pairs[1]);  // addPair(key, value)
nextPair:
            pairs += 2;
            remaining--;
        } while (remaining != 0);
    }

    // Recompute maximum value
    idx = 0;
    *(int *)(this + 0x198) = 0;
    if (*(int *)(this + 0x400) != 0) {
        float *valuePtr = (float *)(*(int *)(this + 0x18c) + 4);
        do {
            float val = *valuePtr;
            if (*(float *)(this + 0x198) <= val && val != *(float *)(this + 0x198)) {
                *(float *)(this + 0x198) = val;
            }
            idx++;
            valuePtr += 2;  // advance to next value (each pair is 8 bytes)
        } while (idx < *(unsigned int *)(this + 0x400));
    }

    return count * 8;  // bytes consumed
}