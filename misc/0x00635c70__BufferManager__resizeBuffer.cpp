// FUNC_NAME: BufferManager::resizeBuffer
// Address: 0x00635c70
// Role: Resizes an internal buffer, allocating memory via FUN_006279a0 and updating pointers.
// Offsets: +0x18 (m_dataEnd), +0x1c (m_data), +0x20 (m_capacity)
// Called when reallocation is needed (e.g., growing a dynamic array).
void __fastcall BufferManager::resizeBuffer(int newCapacity)
{
    int oldCapacity = *(int *)(this + 0x20);  // current capacity

    // Compute the new capacity: if old < new, increase by old+0x14+new? else double old
    if (oldCapacity < newCapacity) {
        newCapacity = oldCapacity + 0x14 + newCapacity;
    } else {
        newCapacity = oldCapacity * 2;
    }

    // Allocate memory: old capacity*8 and new capacity*8 (likely reallocation with copy)
    int newData = FUN_006279a0(oldCapacity * 8, newCapacity * 8);  // allocateMemory

    // Update member fields
    *(int *)(this + 0x1c) = newData;                // m_data
    *(int *)(this + 0x20) = newCapacity;            // m_capacity
    *(int *)(this + 0x18) = newData - 0xa8 + newCapacity * 8;  // m_dataEnd (points past data minus header)

    FUN_00635b50();  // post-resize initialization/copy
}