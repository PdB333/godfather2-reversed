// FUNC_NAME: ResizableBuffer::setCapacity
void __thiscall ResizableBuffer::setCapacity(uint newCapacity)
{
    // +0x04: current allocated capacity (number of elements)
    if (newCapacity > *(uint *)(this + 4)) {
        // Grow: reallocate internal buffer to accommodate new capacity
        FUN_008be050(newCapacity); // likely realloc(buffer, newCapacity * elementSize)
        *(uint *)(this + 4) = newCapacity;
    } else if (newCapacity < *(uint *)(this + 4)) {
        // Shrink: just reduce the capacity marker, no memory reallocation
        *(uint *)(this + 4) = newCapacity;
    }
}