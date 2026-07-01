// FUNC_NAME: Buffer::setCapacity
void __thiscall Buffer::setCapacity(uint newCapacity)
{
    // +0x04: current capacity (uint)
    if (*(uint *)(this + 4) < newCapacity) {
        // Need to allocate larger buffer
        resizeAllocation(newCapacity);
        *(uint *)(this + 4) = newCapacity;
        return;
    }
    // Shrinking: just update capacity without reallocation
    if (newCapacity < *(uint *)(this + 4)) {
        *(uint *)(this + 4) = newCapacity;
    }
}