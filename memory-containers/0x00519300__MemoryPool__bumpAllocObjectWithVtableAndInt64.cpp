// FUNC_NAME: MemoryPool::bumpAllocObjectWithVtableAndInt64
void MemoryPool::bumpAllocObjectWithVtableAndInt64(int32_t arg1, int32_t arg2)
{
    // gMemoryPool + 0x14 holds a pointer to the next free location (bump allocator)
    // This function allocates a 12-byte block: 4 bytes for a vtable pointer, then 8 bytes for data.
    // The data is formed by concatenating arg1 (low) and arg2 (high) into a single 64-bit value.
    // Also stores a fixed vtable pointer (gObjectVtable) at the beginning.

    // Get the bump pointer variable (a pointer to the bump pointer)
    int** bumpPtrVar = reinterpret_cast<int**>(gMemoryPool + 0x14);

    // Write the vtable pointer at the current bump position
    *(*bumpPtrVar) = reinterpret_cast<int>(&gObjectVtable);

    // Advance bump pointer by 4 bytes (size of vtable pointer)
    *bumpPtrVar = *bumpPtrVar + 1; // integer pointer increment advances by 4 bytes

    // Align the bump pointer to a 4-byte boundary (though already aligned after vtable write)
    *bumpPtrVar = reinterpret_cast<int*>((reinterpret_cast<int>(*bumpPtrVar) + 3) & ~3);

    // Write the two 32-bit arguments as a single 64-bit value at the aligned position
    *reinterpret_cast<int64_t*>(*bumpPtrVar) = (static_cast<int64_t>(arg2) << 32) | static_cast<uint32_t>(arg1);

    // Advance the bump pointer by the 8 data bytes
    *bumpPtrVar = *bumpPtrVar + 2; // two ints = 8 bytes

    return;
}