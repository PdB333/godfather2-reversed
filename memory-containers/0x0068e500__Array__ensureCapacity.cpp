// FUNC_NAME: Array::ensureCapacity

struct Array {
    int* data;        // +0x00
    uint32_t size;    // +0x04
    uint32_t capacity; // +0x08
};

void __thiscall Array::ensureCapacity(int* thisPtr, uint32_t newCapacity)
{
    uint32_t* thisBase = (uint32_t*)thisPtr;
    uint32_t oldCapacity = thisBase[2]; // +0x08
    if (oldCapacity < newCapacity) {
        // Allocate new buffer: newCapacity * sizeof(int) bytes
        int* newData = (int*)FUN_009c8e80(newCapacity * sizeof(int));
        int* oldData = (int*)thisBase[0]; // +0x00
        if (oldData != 0) {
            uint32_t count = thisBase[1]; // +0x04
            if (count != 0) {
                for (uint32_t i = 0; i < count; i++) {
                    newData[i] = oldData[i];
                }
            }
            FUN_009c8f10(oldData);
        }
        thisBase[0] = (uint32_t)newData; // +0x00
        thisBase[2] = newCapacity;       // +0x08
    }
}