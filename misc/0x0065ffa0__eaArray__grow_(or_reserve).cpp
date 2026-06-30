// FUNC_NAME: eaArray::grow (or reserve)
// Address: 0x0065ffa0
// Role: Grows the internal buffer to accommodate at least newElementCount elements.
// Assumes element size is 4 bytes. Rounds up capacity to multiple of 16 elements.
// Fields: +0x00 size (uint), +0x04 capacity (uint), +0x08 data (int*)

void __thiscall eaArray::grow(uint newElementCount)
{
    uint currentCapacity = *(uint *)(this + 0x04); // +0x04 capacity
    if (currentCapacity < newElementCount)
    {
        // Round up to multiple of 16 elements
        uint alignedCount = newElementCount + (0x10 - (newElementCount & 0xF));
        int* newData = (int*)malloc(alignedCount * 4); // 4 bytes per element
        int* oldData = *(int**)(this + 0x08); // +0x08 data
        *(int**)(this + 0x08) = newData;

        // Copy old elements to new buffer (FUN_006600e0 likely does memcpy)
        FUN_006600e0(oldData);

        *(int**)(this + 0x08) = oldData; // restore for free?
        free(oldData);
        *(int**)(this + 0x08) = newData;
        *(uint *)(this + 0x04) = alignedCount; // +0x04 capacity
    }
}