// FUNC_NAME: setCapacity
void __thiscall DynamicArray::setCapacity(uint newCapacity)
{
    // +0x04: current capacity
    if (*(uint *)(this + 4) < newCapacity) {
        // Reallocate to larger capacity
        FUN_006b1f00(newCapacity); // likely realloc or allocate
        *(uint *)(this + 4) = newCapacity;
        return;
    }
    if (newCapacity < *(uint *)(this + 4)) {
        // Shrink capacity (no reallocation, just update)
        *(uint *)(this + 4) = newCapacity;
    }
    return;
}