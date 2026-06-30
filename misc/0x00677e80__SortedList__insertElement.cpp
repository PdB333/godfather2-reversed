// FUNC_NAME: SortedList::insertElement

// Function at 0x00677e80: Inserts a new element into a sorted list with duplicate detection.
// The list maintains two arrays: values (m_pValues) and sorted indices (m_pSortedIndices) built as cumulative sums.
// It also stores three keys per element (two shorts, one char) for duplicate comparison.
// When a duplicate is found (same keys as previous element), the max size is decremented and the last value is adjusted.

#include <cstdint>

struct SortedList
{
    // +0x36: Current number of elements in the list
    short m_count;
    // +0x38: Maximum allowed size (or threshold for insertion)
    short m_maxSize;
    // +0x3C: Pointer to sorted indices array (shorts) - cumulative offsets
    short* m_pSortedIndices;
    // +0x40: Pointer to values array (shorts)
    short* m_pValues;
    // +0x44: Pointer to key1 array (shorts)
    short* m_pKey1;
    // +0x48: Pointer to key2 array (shorts)
    short* m_pKey2;
    // +0x4C: Pointer to key3 array (chars)
    char* m_pKey3;

    // This function inserts a new element and recomputes sorted indices.
    // It also checks for duplicates using the three key arrays.
    void __thiscall insertElement()
    {
        // Condition: m_maxSize != 0 and either m_count < 1 or last value is not (m_maxSize - 1)
        if (m_maxSize != 0 &&
            (m_count < 1 || m_pValues[m_count - 1] != m_maxSize - 1))
        {
            // Call helper function (likely does sorting or resizing)
            FUN_00677de0();  // defined elsewhere

            // Insert new value at end: 0 if m_maxSize < 1, otherwise (m_maxSize - 1)
            if (m_maxSize < 1)
            {
                *(int16_t*)((int)m_pValues + m_count * 2) = 0;
            }
            else
            {
                m_pValues[m_count] = m_maxSize - 1;
            }

            // Increment count
            m_count++;

            // Rebuild sorted indices as cumulative sums of (value + 1) for all elements
            int16_t runningSum = 0;
            int16_t idx = 0;
            while (idx < m_count)
            {
                m_pSortedIndices[idx] = runningSum;
                runningSum = m_pValues[idx] + 1;
                idx++;
            }

            // Duplicate detection: compare last inserted element with the one before
            int16_t currentMax = m_maxSize;
            if (currentMax > 0)
            {
                // Offset to last element (shorts)
                int offset = m_count * 2;  // bytes for shorts
                int16_t prevSortedIndex = *(int16_t*)((int)m_pSortedIndices + offset - 2); // s[count-1]
                short* pLastValue = (short*)((int)m_pValues + offset - 2); // pointer to v[count-1]
                int16_t lastValue = *pLastValue;

                // Check if sorted index is less than the value (which implies possible duplicate)
                if (prevSortedIndex < lastValue)
                {
                    int keyIdx1 = (int)prevSortedIndex;
                    int keyIdx2 = (int)lastValue;

                    // Compare three key arrays
                    if (m_pKey1[keyIdx1] == m_pKey1[keyIdx2] &&
                        m_pKey2[keyIdx1] == m_pKey2[keyIdx2] &&
                        m_pKey3[keyIdx1] == m_pKey3[keyIdx2])
                    {
                        // Duplicate found: reduce max size and adjust last value
                        m_maxSize = currentMax - 1;
                        *pLastValue = currentMax - 2;
                    }
                }
            }
        }
    }
};