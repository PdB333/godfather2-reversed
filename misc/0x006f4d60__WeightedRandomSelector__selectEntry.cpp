// FUNC_NAME: WeightedRandomSelector::selectEntry
// Function at 0x006f4d60: Weighted random selection from an array of entries, filtered by time and a condition.
// Each entry is 16 bytes: { uint8_t m_bEnabled; float m_weight; float m_timeThreshold; int32_t m_pad; }
// Class layout:
//   +0x18: m_pHeader (pointer to header struct with count at +0x04)
//   +0x1c: m_pEntries (pointer to array of entries)

class WeightedRandomSelector {
public:
    struct Entry {
        uint8_t  m_bEnabled;      // +0x00: flag checked < 0xff
        float    m_weight;         // +0x04: weight for random selection
        float    m_timeThreshold;  // +0x08: max time for entry to be considered
        int32_t  m_pad;            // +0x0C: padding (4 bytes)
    };

    struct Header {
        int32_t m_count;           // +0x04: number of entries
    };

    // Returns pointer to selected Entry, or null if no valid entry.
    // param_2 = currentTime (float)
    Entry* __thiscall selectEntry(float currentTime) {
        Header* header = *(Header**)(this + 0x18);               // +0x18
        uint32_t count = *(uint32_t*)((int)header + 4);          // header->m_count
        uint32_t index = 0;

        if (count == 0) {
            return nullptr;
        }

        // Allocate temporary weight array (size count * 4)
        float* weightArray = (float*)FUN_006f0640(count);        // likely malloc or scratch buffer
        if (weightArray == nullptr || count == 0) {
            return nullptr;
        }

        float totalWeight = 0.0f;
        int numValid = 0;
        Entry* entry = *(Entry**)(this + 0x1c);                  // +0x1c
        uint32_t localIndex = 0;

        do {
            Entry* currentEntry = entry;
            weightArray[localIndex] = DAT_00d5ccf8;              // store constant (maybe sentinel?)
            if (currentEntry->m_bEnabled < 0xff && (float)currentEntry->m_timeThreshold <= currentTime) {
                if (FUN_006f4d40(currentTime)) {                 // returns nonzero if condition met
                    // (Decompiler shows a loop that does nothing; omitted as it's likely a compiler artifact)
                    numValid++;
                    totalWeight += (float)currentEntry->m_weight;
                    weightArray[localIndex] = (float)currentEntry->m_weight;
                }
            }
            localIndex++;
            entry = (Entry*)((uint32_t*)currentEntry + 4);      // advance to next entry (16 bytes)
        } while (localIndex < count);

        if (numValid == 0) {
            return (Entry*)entry;                                // return pointer to last processed entry (sentinel?)
        }

        // Weighted random selection
        int randVal = _rand();
        float randomFloat = (float)randVal * DAT_00e44590 * totalWeight;  // RAND_MAX scaling constant

        uint32_t selectedIndex = 0;
        uint32_t limit = count - 1;
        if (selectedIndex + 3 < limit) {
            float* pWeight = weightArray + 2;                    // unrolled loop
            do {
                // Check every 4th weight from the array
                // (implementation matches Ghidra unrolled logic)
                if (pWeight[-2] >= 0.0f) {
                    randomFloat -= pWeight[-2];
                    if (randomFloat < 0.0f) goto found;
                }
                if (pWeight[-1] >= 0.0f) {
                    randomFloat -= pWeight[-1];
                    if (randomFloat < 0.0f) {
                        selectedIndex += 1;
                        goto found;
                    }
                }
                if (pWeight[0] >= 0.0f) {
                    randomFloat -= pWeight[0];
                    if (randomFloat < 0.0f) {
                        selectedIndex += 2;
                        goto found;
                    }
                }
                if (pWeight[1] >= 0.0f) {
                    randomFloat -= pWeight[1];
                    if (randomFloat < 0.0f) {
                        selectedIndex += 3;
                        goto found;
                    }
                }
                selectedIndex += 4;
                pWeight += 4;
            } while (selectedIndex < count - 4);
        }

        if (selectedIndex < limit) {
            do {
                float weight = *(float*)((int)weightArray + selectedIndex * 4);
                if (weight < 0.0f) {
                    // skip negative weights
                } else {
                    randomFloat -= weight;
                    if (randomFloat < 0.0f) break;
                }
                selectedIndex++;
            } while (selectedIndex < limit);
        }

found:
        // Return pointer to the selected entry (base + index * 16)
        Entry* baseEntry = *(Entry**)(this + 0x1c);
        return (Entry*)((uint8_t*)baseEntry + selectedIndex * 16);
    }
};