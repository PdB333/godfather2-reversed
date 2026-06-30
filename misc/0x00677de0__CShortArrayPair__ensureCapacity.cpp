// FUNC_NAME: CShortArrayPair::ensureCapacity
void __thiscall CShortArrayPair::ensureCapacity(short newMaxSize)
{
    int *newBuffer;
    int *oldBuffer1;
    short count;
    short i;

    // Check if we need to grow: m_maxSize is at offset +4 (low 16 bits of int)
    if (*(short *)((int *)this + 1) < newMaxSize) {
        // Update capacity
        *(short *)((int *)this + 1) = newMaxSize;

        // Allocate a new contiguous block for both arrays
        // FUN_00673070 allocates (newMaxSize * 2) shorts for each array? It returns a pointer.
        newBuffer = (int *)FUN_00673070(); // Returns allocated block (int pointer for alignment)
        count = *(short *)((int)this + 0x36); // m_count at offset 0x36

        // Copy existing data from old buffers to new block
        // m_pBuffer1 is at offset 0x3C (this[0xf] as int)
        // m_pBuffer2 is at offset 0x40 (this[0x10] as int)
        if (0 < count) {
            for (i = 0; i < count; i++) {
                // Copy m_pBuffer1[i] to newBuffer[i]
                *(short *)((int)newBuffer + i * 2) = *(short *)(*(int *)&this->field_0x3c + i * 2); // simplified
                // Copy m_pBuffer2[i] to newBuffer + newMaxSize * 2
                *(short *)((int)newBuffer + newMaxSize * 2 + i * 2) = *(short *)(*(int *)&this->field_0x40 + i * 2);
            }
        }

        // Free old buffer1 if it's not the inline buffer (at offset 0x14 = this + 5 as int)
        oldBuffer1 = (int *)this->field_0x3c; // m_pBuffer1
        if ((oldBuffer1 != (int *)((int)this + 0x14)) && (oldBuffer1 != (int *)0x0)) {
            // Custom deallocation using memory manager
            // *(int *)(*(int *)(some global + 0xc) + (header[1]) * 4) = 0;
            // Decrement allocation count
            // Call free function pointer DAT_01206694
            *(int *)(*(int *)(this->field_0x00 + 0xc) + *(oldBuffer1 - 2) * 4) = 0;
            (*(int *)(this->field_0x00 + 4))--; // Decrement alloc count at +4
            ((void (*)(int *))DAT_01206694)(oldBuffer1 - 4); // Free header
        }

        // Update pointers to new buffers
        this->field_0x3c = (int)newBuffer; // m_pBuffer1
        this->field_0x40 = (int)((int)newBuffer + newMaxSize * 2); // m_pBuffer2 starts after first array
    }
}