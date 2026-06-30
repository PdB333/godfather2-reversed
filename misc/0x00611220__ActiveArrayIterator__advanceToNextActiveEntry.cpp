// FUNC_NAME: ActiveArrayIterator::advanceToNextActiveEntry
// Function address: 0x00611220
// Searches through an array of ints until a non-zero value is found, starting from the current index.
// Structure fields:
//   +0x00 : int* m_pArray       // pointer to array of ints
//   +0x04 : uint  m_currentIndex // current index into array
//   +0x08 : int   m_currentValue // value at current index (updated with first non-zero found)

void __thiscall ActiveArrayIterator::advanceToNextActiveEntry(void)
{
    // Get current index
    uint index = this->m_currentIndex;

    // If the array pointer is null, nothing to iterate
    if (this->m_pArray != (int *)0x0) {
        do {
            // Bounds check: max index 4095
            if (index > 0xfff) {
                return;
            }
            // Read value at current index
            int value = this->m_pArray[index];
            // Store it (may be zero or non-zero)
            this->m_currentValue = value;
            // Advance index
            this->m_currentIndex = index + 1;
            // If value is non-zero, we are done (value stored in m_currentValue)
            if (value != 0) {
                return;
            }
            // Otherwise continue with next index
            index = this->m_currentIndex;
        } while( true );
    }
    return;
}