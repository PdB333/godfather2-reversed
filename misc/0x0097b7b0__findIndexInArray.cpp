// FUNC_NAME: findIndexInArray
// Function at 0x0097b7b0: Linear search for an integer in a member array.
// Returns index (0-based) or 0xFFFFFFFF if not found.

class SomeClass {
public:
    // Offsets:
    //   +0x58: m_pArray (int*) - pointer to array of ints
    //   +0x78: m_arrayCount (unsigned int) - number of elements in the array
    unsigned int findIndex(int searchValue) const {
        if (m_arrayCount == 0)
            return 0xFFFFFFFF;

        for (unsigned int i = 0; i < m_arrayCount; ++i) {
            if (m_pArray[i] == searchValue)
                return i;
        }
        return 0xFFFFFFFF;
    }

private:
    int* m_pArray;            // +0x58
    unsigned int m_arrayCount; // +0x78
};