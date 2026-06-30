// FUNC_NAME: BufferManager::updatePointer
void __thiscall BufferManager::updatePointer(int thisPtr)
{
    // +0x18: current pointer (output)
    // +0x1c: base pointer
    // +0x20: element index (each element size 8)
    int base = *(int*)(thisPtr + 0x1c);
    int index = *(int*)(thisPtr + 0x20);
    *(int*)(thisPtr + 0x18) = base + (index - 1) * 8;

    // +0x2c: capacity (word)
    unsigned short capacity = *(unsigned short*)(thisPtr + 0x2c);
    if (capacity > 0x1000)
    {
        // +0x14: start offset (or pointer to first element)
        // +0x28: end offset (or pointer to last element)
        // Element size for count calculation: 0x18 (24 bytes)
        int start = *(int*)(thisPtr + 0x14);
        int end = *(int*)(thisPtr + 0x28);
        int count = ((end - start) / 0x18) + 1;
        if (count < 0x1000)
        {
            // Reallocate or adjust buffer
            FUN_00635c10(); // Expand buffer
        }
    }
}