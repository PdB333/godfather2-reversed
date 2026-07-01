// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(uint32_t value)
{
    int32_t newCapacity;
    int32_t capacity = *(int32_t *)(this + 0x9c); // +0x9c: capacity
    int32_t size = *(int32_t *)(this + 0x98); // +0x98: current size

    if (size == capacity) {
        // Double capacity or set to 1 if empty
        newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Reallocate internal buffer to new capacity
        DynamicArray::reallocate(newCapacity); // 0x00849170
    }

    // Write value at the end of the array
    uint32_t *data = *(uint32_t **)(this + 0x94); // +0x94: data pointer
    data[size] = value;

    // Increment size
    *(int32_t *)(this + 0x98) = size + 1;
}