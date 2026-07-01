// FUNC_NAME: binarySearchLowerBound_0x50
// Address: 0x00889090
// Role: Binary search lower bound for an array of 0x50-byte structures, comparing uint32 at offset +0x8.
// Returns pointer to first element where key >= search key, or end if not found.

int* binarySearchLowerBound_0x50(int* arrayBegin, int* arrayEnd, int* keyStruct)
{
    int count = (arrayEnd - arrayBegin) / 0x50; // Number of elements (each 0x50 bytes)
    int* result = arrayBegin;
    int step;

    while (count > 0) {
        step = count >> 1;
        int* mid = result + step * 0x50; // Mid element address
        // Compare uint32 at offset +0x8
        if (*(uint32_t*)(mid + 8) < *(uint32_t*)(keyStruct + 8)) {
            result = mid + 0x50; // Move lower bound up
            count = count - step - 1;
        } else {
            count = step;
        }
    }
    return result;
}