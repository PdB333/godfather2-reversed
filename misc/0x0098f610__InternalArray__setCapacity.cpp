// FUNC_NAME: InternalArray::setCapacity
void __thiscall InternalArray::setCapacity(uint newCapacity)
{
    // +0x4: current capacity (uint)
    if (*(uint *)(this + 4) < newCapacity) {
        // Grow: reallocate internal buffer to new capacity
        reallocate(newCapacity);
        *(uint *)(this + 4) = newCapacity;
        return;
    }
    // Shrink: just update capacity (no reallocation)
    if (newCapacity < *(uint *)(this + 4)) {
        *(uint *)(this + 4) = newCapacity;
    }
}