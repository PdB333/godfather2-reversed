// FUNC_NAME: ArrayContainer::reserve
void __thiscall ArrayContainer::reserve(int *this, uint newCapacity)
{
    int *newData;
    int *oldData;
    uint elementSize;
    uint copyCount;
    uint i;

    if ((uint)this[2] < newCapacity) {
        // Allocate new memory: each element is 0xC (12) bytes
        newData = (int *)FUN_009c8e80(newCapacity * 0xc);
        if (this[0] != 0) {
            // Copy existing elements up to current count
            copyCount = 0;
            if (this[1] != 0) {
                oldData = this[0];
                i = 0;
                do {
                    // Copy one element (12 bytes)
                    newData[i] = oldData[i];
                    newData[i + 1] = oldData[i + 1];
                    newData[i + 2] = oldData[i + 2]; // inferred third int
                    copyCount++;
                    i += 3; // 3 ints per element
                } while (copyCount < (uint)this[1]);
            }
            // Free old memory
            FUN_009c8f10(this[0]);
        }
        // Update pointer and capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    // Note: this[1] (count) is not changed
}