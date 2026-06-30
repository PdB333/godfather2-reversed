// FUNC_NAME: GrowingArray::add
void __thiscall GrowingArray::add(undefined4 value)
{
    // +0x14: current element count
    // +0x18: capacity (number of allocated slots)
    int count = *(int *)(this + 0x14);
    int capacity = *(int *)(this + 0x18);

    // Grow if full
    if (count == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocates internal array; assumed to update +0x10 (pointer) and +0x18 (capacity)
        FUN_006f9120(newCapacity);
    }

    // +0x10: pointer to array of `undefined4`
    undefined4 *array = *(undefined4 **)(this + 0x10);
    *(int *)(this + 0x14) = count + 1;  // increment count

    if (array != (undefined4 *)0x0) {
        array[count] = value;
    }
}