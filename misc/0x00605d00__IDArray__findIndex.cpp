// FUNC_NAME: IDArray::findIndex
// Address: 0x00605d00
// Binary search on sorted array of unsigned ints.
// Returns 1 if found, writes index to outIndex; returns 0 if not found.

class IDArray {
public:
    // +0x10: int count
    // +0x18: uint* data (sorted, unique values)
    int count;
    unsigned int* data;

    // __thiscall
    int findIndex(unsigned int key, int* outIndex) const {
        int low = 0;
        int high = this->count - 1;
        if (high < 0) {
            return 0;
        }

        do {
            int mid = (high + low) / 2;
            unsigned int value = this->data[mid];
            if (key == value) {
                *outIndex = mid;
                return 1;
            }
            if (key < value) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } while (low <= high);

        return 0;
    }
};