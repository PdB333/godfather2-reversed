// FUNC_NAME: PairList::removePairByKey
// Function address: 0x004a6400
// Removes a pair from a dynamic array of 8-byte (key + value) entries by matching the key.
// Iterates through the array, finds the entry with the given key, shifts all subsequent entries
// left by one slot, and decrements the count. No memory deallocation is performed.
// Class layout:
//   +0x74: int** m_pairs          // pointer to array of {int, int} pairs (8 bytes each)
//   +0x78: int   m_count          // number of valid entries in the array

class PairList {
public:
    int** m_pairs;   // +0x74
    int   m_count;   // +0x78

    // __fastcall in GCC/MSVC style: this in ECX, key in EDX
    void __fastcall removePairByKey(int key);
};

void __fastcall PairList::removePairByKey(int key)
{
    unsigned int i = 0;
    if (m_count != 0) {
        int** iter = m_pairs;                 // pointer to first entry
        while (iter[0] != key) {              // compare first int (key) of each pair
            ++i;
            iter += 2;                         // advance to next pair (8 bytes)
            if ((unsigned int)m_count <= i) {
                return;                        // key not found
            }
        }
        // Found the entry at index i
        if (i < (unsigned int)(m_count - 1)) {
            // Shift all subsequent entries left by one slot
            do {
                int* dst = m_pairs[i];         // base of current entry (2 ints)
                int* src = m_pairs[i + 1];     // base of next entry
                dst[0] = src[0];               // copy key
                dst[1] = src[1];               // copy value
                ++i;
            } while (i < (unsigned int)(m_count - 1));
        }
        m_count--;                             // decrement count
    }
}