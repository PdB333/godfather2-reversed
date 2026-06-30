// FUNC_NAME: DynamicArray::reserveCapacity
// Address: 0x006afc10
// Reconstructed C++ method for a dynamic array of 8-byte elements (e.g., uint64 or a struct of two 4-byte values).
// The class has three fields:
//   +0x00: data pointer (int*)
//   +0x04: element count (uint)
//   +0x08: capacity (uint)
// Element size is 8 bytes.

void __thiscall DynamicArray::reserveCapacity(int* thisPtr, uint newCapacity)
{
    int* oldData;
    uint elementCount;
    uint oldCapacity;
    int* newData;

    oldCapacity = (uint)thisPtr[2]; // capacity

    if (oldCapacity < newCapacity) {
        // Allocate new buffer (8 bytes per element)
        newData = (int*)FUN_009c8e80(newCapacity * 8); // allocateMemory
        oldData = (int*)thisPtr[0]; // current data pointer

        if (oldData != 0) {
            elementCount = (uint)thisPtr[1]; // current element count
            if (elementCount != 0) {
                // Copy existing elements (2 ints per element)
                for (uint i = 0; i < elementCount; i++) {
                    newData[i * 2] = oldData[i * 2];
                    newData[i * 2 + 1] = oldData[i * 2 + 1];
                }
            }
            // Free the old buffer
            FUN_009c8f10(oldData); // freeMemory
        }

        // Update the array state
        thisPtr[0] = (int)newData;
        thisPtr[2] = (int)newCapacity; // capacity
    }
    // If newCapacity <= oldCapacity, do nothing
    return;
}