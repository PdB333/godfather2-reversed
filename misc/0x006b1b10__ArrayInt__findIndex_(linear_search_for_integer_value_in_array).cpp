// FUNC_NAME: ArrayInt::findIndex (linear search for integer value in array)
// Function address: 0x006b1b10
// Member function of a simple container class holding an array of ints.
// Structure layout:
//   +0x00: int* m_array   (pointer to array of ints)
//   +0x04: int  m_size    (number of elements in array)
// Returns 0xffffffff (-1) if not found, else the index.

uint __thiscall ArrayInt::findIndex(int value) const
{
    // If array is non-null, search linearly
    if (this->m_size != 0) {
        int* current = this->m_array;
        uint index = 0;
        while (*current != value) {
            index++;
            current++;
            if ((uint)this->m_size <= index) {
                return 0xffffffff; // not found
            }
        }
        return index; // found
    }
    return 0xffffffff; // empty array
}