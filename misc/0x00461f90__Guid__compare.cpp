// FUNC_NAME: Guid::compare
// Address: 0x00461f90
// Comparison function for 128-bit (4 int) GUID-like structures.
// Returns 0 if identical, 1 if different.

class Guid {
public:
    int data[4]; // 16 bytes total

    int __thiscall compare(const Guid& other) const {
        if (data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2] &&
            data[3] == other.data[3]) {
            return 0; // equal
        }
        return 1; // not equal
    }
};