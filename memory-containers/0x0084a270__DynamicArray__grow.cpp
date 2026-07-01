// FUNC_NAME: DynamicArray::grow
// Function address: 0x0084a270
// Role: Resize a dynamic array with 8-byte elements (two 32-bit words per element).
// Allocates a new buffer if requested capacity exceeds current capacity, copies old data, frees old.

void __thiscall DynamicArray::grow(int *this, uint newCapacity) {
    int *oldData;
    int *newData;
    uint i;

    // Only grow if new capacity is larger than current capacity
    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer: each element is 8 bytes
        newData = (int *)FUN_009c8e80(newCapacity * 8);
        if (this[0] != 0) {
            // Copy existing elements (each 8 bytes) from old to new
            for (i = 0; i < (uint)this[1]; ++i) {
                newData[i * 2] = ((int *)this[0])[i * 2];     // first word
                newData[i * 2 + 1] = ((int *)this[0])[i * 2 + 1]; // second word
            }
            // Free old buffer
            FUN_009c8f10(this[0]);
        }
        // Update: pointer, capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    // Note: this[1] (count) is not updated here; caller must adjust.
}