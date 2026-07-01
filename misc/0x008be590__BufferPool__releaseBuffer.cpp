// FUNC_NAME: BufferPool::releaseBuffer
void __thiscall BufferPool::releaseBuffer(void* handle, uint size)
{
    // +0x140: m_usedCount - number of bytes currently allocated from pool
    if (size <= this->m_usedCount)
    {
        this->m_usedCount -= size;

        // validate whether 'handle' is a valid allocation from this pool
        int isValid = validateHandle(handle);  // FUN_006b0ee0
        if (isValid != 0)
        {
            // query the total capacity of the pool (e.g. maximum allocatable size)
            uint totalCapacity = getTotalCapacity();  // FUN_006b18a0
            if (size <= totalCapacity)
            {
                // perform actual deallocation of the memory block
                deallocateBuffer(size);  // FUN_006b64b0
            }
        }
    }
}