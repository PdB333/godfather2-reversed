// FUNC_NAME: IntArray::findIndex
// Function address: 0x00411f60
// Searches for a value in a fixed-size array (32 ints) and returns its index.
// Returns 0xFFFFFFFF if not found.

class IntArray {
public:
    // +0x00: int m_data[32];
    // +0x80: uint m_count;

    __thiscall uint findIndex(const int &value) const {
        uint count = *(uint *)(this + 0x80);
        if (count == 0) {
            return 0xFFFFFFFF;
        }

        for (uint i = 0; i < count; i++) {
            if (*(int *)(this + i * 4) == value) {
                return i;
            }
        }

        return 0xFFFFFFFF;
    }
};