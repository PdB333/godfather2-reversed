// FUNC_NAME: PriorityQueue::extractMinimum
// Address: 0x006322f0
// Role: Finds the minimum value among entries (types 3 and 4) and appends a new type-3 entry with that value.

class PriorityQueue {
public:
    // +0x08: pointer to end of buffer (one past last entry)
    // +0x0c: pointer to start of buffer
    // +0x10: pointer to capacity or alternate base
    // +0x40: pointer to alternate base for negative indices
    // Each entry: 8 bytes (int type, float value)

    int extractMinimum() {
        int* pBegin = *(int**)(this + 0x0c);
        int* pEnd = *(int**)(this + 0x08);
        int count = (pEnd - pBegin) >> 3; // number of entries

        float minValue;
        int* pCurrent = pBegin;

        // Handle first entry
        if (pEnd <= pBegin || pBegin == nullptr) {
            goto defaultMin;
        }

        if (*pBegin == 3) {
            minValue = *(float*)(pBegin + 1);
        } else if (*pBegin == 4) {
            float temp;
            if (validateEntry(&temp)) {
                // Treat as type 3 with validated value
                int tempType = 3;
                float tempValue = temp;
                pCurrent = &tempType; // point to stack entry
                minValue = temp;
            } else {
                goto defaultMin;
            }
        } else {
            goto defaultMin;
        }

        // If minValue equals sentinel, try to find a valid entry
        if (minValue == DAT_00e2b05c) {
            while (true) {
                pCurrent = *(int**)(this + 0x0c);
                pEnd = *(int**)(this + 0x08);
                if (pEnd <= pCurrent || pCurrent == nullptr) {
                    break;
                }
                if (*pCurrent == 3) {
                    minValue = *(float*)(pCurrent + 1);
                    break;
                } else if (*pCurrent == 4) {
                    float temp;
                    if (validateEntry(&temp)) {
                        minValue = temp;
                        break;
                    }
                }
                // If not valid, log error and continue
                debugLog(PTR_s_number_00e2a8a8);
            }
            if (pEnd <= pCurrent || pCurrent == nullptr) {
                minValue = 0.0f;
            }
        }

        // Iterate over remaining entries (index 2 to count)
        if (count > 1) {
            for (int index = 2; index <= count; ++index) {
                float currentValue = getEntryValueAtIndex(this, index);
                if (currentValue == 0.0f) {
                    // Find a valid entry at this index
                    int* pEntry = nullptr;
                    if (index < 1) {
                        pEntry = nullptr;
                    } else {
                        pEntry = (int*)(*(int*)(this + 0x0c) - 8 + index * 8);
                        if (pEntry >= *(int**)(this + 0x08)) {
                            // Invalid index, try negative index handling
                            if (index < -9999) {
                                if (index == -0x2711) {
                                    pEntry = (int*)(this + 0x40);
                                } else if (index == -10000) {
                                    pEntry = (int*)(*(int*)(this + 0x10) + 0x2c);
                                } else {
                                    int base = *(int*)(*(int*)(this + 0x0c) - 4);
                                    int offset = -0x2711 - index;
                                    if ((int)(unsigned char)*(byte*)(base + 7) < offset) {
                                        pEntry = nullptr;
                                    } else {
                                        pEntry = (int*)(base + 8 + offset * 8);
                                    }
                                }
                            } else {
                                pEntry = (int*)(*(int*)(this + 0x08) + index * 8);
                            }
                        }
                    }
                    // Validate the entry
                    while (pEntry == nullptr ||
                           (*pEntry != 3 && (*pEntry != 4 || !validateEntry(&temp)))) {
                        // Log error and try again? This loop seems infinite if condition never met.
                        // Original code has a do-while that may loop indefinitely.
                        // We'll keep the structure but note it's problematic.
                        debugLog(PTR_s_number_00e2a8a8);
                        // Recompute pEntry? Original code jumps back to LAB_0063246b.
                        // This is a simplification; actual logic may be different.
                        break;
                    }
                    if (pEntry != nullptr) {
                        currentValue = *(float*)(pEntry + 1);
                    }
                }
                if (currentValue < minValue) {
                    minValue = currentValue;
                }
            }
        }

        // Append new entry at end
        pEnd = *(int**)(this + 0x08);
        *pEnd = 3;
        *(float*)(pEnd + 1) = minValue;
        *(int*)(this + 0x08) = (int)pEnd + 8;
        return 1;

    defaultMin:
        minValue = 0.0f;
        // Fall through to append
        pEnd = *(int**)(this + 0x08);
        *pEnd = 3;
        *(float*)(pEnd + 1) = minValue;
        *(int*)(this + 0x08) = (int)pEnd + 8;
        return 1;
    }

private:
    // Helper functions (callees)
    bool validateEntry(float* outValue);
    void debugLog(const char* message);
    float getEntryValueAtIndex(PriorityQueue* obj, int index);

    static const float DAT_00e2b05c; // sentinel value
    static const char* PTR_s_number_00e2a8a8; // debug string
};