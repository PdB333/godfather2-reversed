// FUNC_NAME: EARSIntArray::find
class EARSIntArray {
public:
    int* m_data;   // +0x00: pointer to integer array
    int m_size;    // +0x04: number of elements in the array

    // Linear search for the first occurrence of the value pointed to by pValue.
    // Returns the index if found, or 0xFFFFFFFF if not found.
    __thiscall uint find(const int* pValue) const {
        uint index = 0xFFFFFFFF;
        if (m_size != 0) {
            int* cur = m_data;
            index = 0;
            while (*cur != *pValue) {
                index++;
                cur++;
                if ((uint)m_size <= index) {
                    return 0xFFFFFFFF;
                }
            }
        }
        return index;
    }
};