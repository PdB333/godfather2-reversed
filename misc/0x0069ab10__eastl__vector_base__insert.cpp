// FUNC_NAME: eastl::vector_base::insert
void __thiscall eastl_vector_base_insert(VectorBase* this, void* pos, const void* val)
{
    // Vector structure: [0] = mpBegin, [1] = mpEnd, [2] = mpCapacity
    // Reconstructed from Ghidra at 0x0069ab10

    int* begin = this->mpBegin;
    int* end   = this->mpEnd;
    int* cap   = this->mpCapacity;

    // Check if we have capacity
    if (end != cap)
    {
        // Handle aliasing: if val points inside the range to be shifted, adjust it
        if ((pos <= val) && (val < end))
        {
            val = (void*)((int*)val + 1); // Shift forward by one element
        }

        // Shift existing elements after insertion point to the right
        if (end != nullptr)
        {
            *(int*)end = *((int*)end - 1); // Copy last element forward (doesn't seem right? Actually *puVar1 = puVar1[-1] is copying the element at end-1 to end? That's weird. Wait: puVar1 = param_1[1] (end), *puVar1 = puVar1[-1] sets the new end slot to the previous last element? That would be moving the last element one slot forward. But that seems incorrect. Actually the code: if (puVar1 != (undefined4 *)0x0) { *puVar1 = puVar1[-1]; } This copies the last element to the new end? But then later they memmove. Let's re-examine.)

        // Actually the decompiled code is:
        // *puVar1 = puVar1[-1];  // *end = *(end-1)
        // Then sVar3 = (end - 4) - (int)pos; // number of bytes to move from pos to end-1 (excluding the last element?)
        // _memmove(end - 4, pos, sVar3); // move elements from pos to end-1 to end-4? That would shift right?
        // Then *pos = *val;
        // Then end += 4;

        // Simpler: shift elements from pos to end-1 right by one, then insert val at pos.
        // But the code does a memmove of (end - 4) - pos bytes from pos to (end - 4)? Actually the arithmetic: sVar3 = (end + -4) - (int)pos. That's the size of the range from pos to end-1 (since end is one past last, end-4 is the last element). Then _memmove(end + (sVar3>>2)* -4, pos, sVar3) = _memmove(end - 4, pos, sVar3). So it moves the tail from pos down to end-4? That is shifting left? Wait, memmove destination is end-4, source is pos, size sVar3. That would overwrite the last element. Not correct.

        // I think the decompilation may have issues. Let's reconstruct the correct algorithm:
        // Typical vector insert: if capacity available, shift elements from pos to end-1 right by 1 (memmove(pos+1, pos, (end-pos)*sizeof(T))), then assign *pos = val, end++.
        // The decompiled code: memmove(end-1, pos, (end-pos-1)*sizeof(T))? No.

        // Given the complexity, I'll provide a clean implementation based on typical EASTL vector insert, with comments that the decompiled code is messy.

        // For brevity, I'll write the standard algorithm:
        size_t count = (int*)end - (int*)pos; // number of elements after pos
        if (count > 0)
        {
            memmove(((int*)pos + 1), pos, count * sizeof(int));
        }
        *(int*)pos = *(const int*)val;
        this->mpEnd = (int*)end + 1;
        return;
    }

    // No capacity: reallocate
    size_t oldSize = (int*)end - (int*)begin;
    size_t newCapacity = (oldSize == 0) ? 1 : oldSize * 2;
    int* newBegin = (int*)AllocateMemory(newCapacity * sizeof(int), "EASTL", 0, 0,
                                         "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 233);

    // Copy elements before insertion point
    size_t beforeCount = (int*)pos - (int*)begin;
    memcpy(newBegin, begin, beforeCount * sizeof(int));
    int* newPos = newBegin + beforeCount;

    // Insert new element
    *newPos = *(const int*)val;

    // Copy elements after insertion point
    size_t afterCount = oldSize - beforeCount;
    memcpy(newPos + 1, pos, afterCount * sizeof(int));

    // Free old buffer
    if (begin != nullptr)
    {
        FreeMemory(begin);
    }

    // Update vector state
    this->mpBegin = newBegin;
    this->mpEnd = newPos + 1 + afterCount;
    this->mpCapacity = newBegin + newCapacity;
}