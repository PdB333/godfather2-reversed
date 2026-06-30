// FUNC_NAME: filterMatchingIndices
// Address: 0x004c4fb0
// This function filters items from a flagged collection based on two masks (byte and word),
// storing matching indices into an output buffer and updating the result count.
// The collection can either iterate over all items sequentially or over a precomputed index list terminated by 0xFFFF.

class FlaggedCollection {
public:
    // Offsets (relative to this):
    // +0x08: m_pByteFlags (byte*)     - per-item byte flags
    // +0x0c: m_pUShortFlags (ushort*) - per-item ushort flags
    // +0x14: m_pIndexList (ushort*)   - index list for non-sequential iteration
    // +0x1a: m_numResults (ushort)    - number of matching indices
    // +0x1c: m_pResultIndices (ushort*) - output buffer for matching indices
    // +0x38: m_numItems (int)         - total items (for sequential case)
    // +0x3c: m_bUseIndexList (byte)   - if non-zero, iterate using m_pIndexList

    void filterMatchingIndices(uint16_t mask) {
        uint8_t byteMask = (uint8_t)(mask & 0xFF);
        uint16_t wordMask = (uint16_t)(mask >> 8);
        uint16_t resultCount = 0;

        if (m_bUseIndexList == 0) {
            // Sequential scan over all items
            for (uint16_t i = 0; (int)i < m_numItems; i++) {
                if (((m_pByteFlags[i] & byteMask) == byteMask) &&
                    ((m_pUShortFlags[i] & wordMask) == wordMask)) {
                    m_pResultIndices[resultCount++] = i;
                }
            }
        } else {
            // Iterate over index list terminated by 0xFFFF
            uint16_t listIndex = 0;
            uint16_t itemIndex;
            do {
                itemIndex = m_pIndexList[listIndex];
                listIndex++;
                if (((m_pByteFlags[itemIndex] & byteMask) == byteMask) &&
                    ((m_pUShortFlags[itemIndex] & wordMask) == wordMask)) {
                    m_pResultIndices[resultCount++] = itemIndex;
                }
            } while (itemIndex != 0xFFFF);
        }

        m_numResults = resultCount;
    }

    // Member variables (declared for completeness; actual layout matches offsets)
    byte* m_pByteFlags;          // +0x08
    uint16_t* m_pUShortFlags;    // +0x0c
    uint16_t* m_pIndexList;      // +0x14
    uint16_t m_numResults;       // +0x1a
    uint16_t* m_pResultIndices;  // +0x1c
    int m_numItems;              // +0x38
    byte m_bUseIndexList;        // +0x3c
};