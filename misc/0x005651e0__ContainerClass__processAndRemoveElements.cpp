// FUNC_NAME: ContainerClass::processAndRemoveElements
// Address: 0x005651e0
// This function iterates backward over an array, calls a processing function for each element,
// and then performs a removal/shift operation. The processing function may modify the count.
// Offsets:
//   +0x22c - uint32_t m_count (number of elements)
//   +0x128 - uint32_t* m_array1 (primary array of 4-byte elements)
//   +0x12c - uint32_t* m_array2 (secondary array, possibly overlapping with m_array1+4)

void ContainerClass::processAndRemoveElements()
{
    uint32_t i = m_count;                    // start from current count

    while (i > 0)
    {
        i--;                                 // decrement first (loop from count-1 down to 0)

        // Call a function that may examine or remove the element at index i
        // (likely modifies m_count)
        callProcessingFunc();

        uint32_t newCount = m_count;         // re-fetch count after processing

        if (i < newCount)                    // if element at i still exists (count did not drop below i)
        {
            if (i < newCount - 1)            // if i is not the last valid index
            {
                // Copy the element at index newCount (the old last element) to index i in the second array.
                // This effectively moves the last element into the spot of the element that was just processed.
                m_array2[i] = m_array1[newCount];
            }

            m_count--;                       // decrement count after the shift (removes the last element)
        }
    }
}