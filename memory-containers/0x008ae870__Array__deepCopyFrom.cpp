// FUNC_NAME: Array::deepCopyFrom
int* __thiscall Array::deepCopyFrom(int* thisPtr, int* other)
{
    // +0x00: data pointer (int*)
    // +0x04: count (int)
    // +0x08: capacity (int)
    // Each element is 16 bytes (0x10)

    int capacity = other[2];          // other's capacity
    thisPtr[2] = capacity;            // copy capacity
    thisPtr[1] = other[1];            // copy count

    if (capacity == 0) {
        thisPtr[0] = 0;               // null data pointer
        return thisPtr;
    }

    // Allocate memory for capacity elements (each 16 bytes)
    int* newData = (int*)FUN_009c8e80(capacity << 4);
    thisPtr[0] = (int)newData;

    if (thisPtr[1] != 0) {
        for (uint i = 0; i < (uint)thisPtr[1]; i++) {
            // Check if destination slot is non-null (likely always true)
            if (newData[i] != 0) {
                // Copy source element at offset i*16 to destination
                FUN_004d3b50(other[0] + i * 16);
            }
        }
    }

    return thisPtr;
}