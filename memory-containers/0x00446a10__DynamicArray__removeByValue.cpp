// FUNC_NAME: DynamicArray::removeByValue
void __thiscall DynamicArray::removeByValue(int value)
{
    uint count = *(uint *)(this + 0x20); // +0x20: number of elements
    uint index = 0xffffffff; // Sentinel for not found
    if (count != 0) {
        uint i = 0;
        do {
            index = i;
            if (*(int *)(this + 0x18 + i * 4) == value) break; // +0x18: start of array
            i = i + 1;
            index = 0xffffffff;
        } while (i < count);
    }
    if (index < count) {
        // Shift elements left to remove the found element
        if (index < count - 1) {
            do {
                *(int *)(this + 0x18 + index * 4) = *(int *)(this + 0x1c + index * 4);
                index = index + 1;
            } while (index < (uint)(*(int *)(this + 0x20) - 1));
        }
        *(int *)(this + 0x20) = *(int *)(this + 0x20) - 1; // Decrement count
    }
}