// FUNC_NAME: TNLConnection::allocateSendBuffer
// Address: 0x005e8510
// Reconstructed C++ for The Godfather 2 (EA EARS engine, x86, __thiscall)

bool TNLConnection::allocateSendBuffer()
{
    bool bResult = false;
    
    // Get memory manager global (singleton) - likely EARS MemoryManager
    MemoryManager* memMgr = *(MemoryManager**)0x01223510;
    
    // Call vtable functions at offsets 0x58 and 0x60
    int totalSize = memMgr->getTotalSize();         // vtable[0x58]
    int alignment = memMgr->getAlignment();         // vtable[0x60]
    
    if (totalSize != 0)
    {
        // Accumulate total required size (this->m_sendSize + totalSize)
        this->m_sendSize += totalSize;
        
        // Calculate size to allocate (rounded up alignment)
        int allocSize = this->m_sendSize - 1 + alignment;
        
        int allocatedPtr = 0;
        // Check if allocator is available and size > 0
        Allocator* allocator = *(Allocator**)0x01223518;
        if (allocator != nullptr && allocator->m_pAllocateFunc != nullptr && allocSize != 0)
        {
            // Call allocator function: void* allocate(size_t size, AllocFlags flags)
            // Flags: 0x00020004 (2 = align? 4 = zero?) - stored on stack
            unsigned int stackFlags[3];
            stackFlags[0] = 2;      // possible alignment flag
            stackFlags[1] = 4;      // possible zero flag
            stackFlags[2] = 0;
            allocatedPtr = allocator->m_pAllocateFunc(allocSize, stackFlags);
        }
        
        // Store allocated pointer and aligned address
        this->m_pSendBuffer = allocatedPtr;
        this->m_alignedSendPtr = (allocatedPtr - 1 + alignment) & ~(alignment - 1);
        
        if (allocatedPtr == 0)
        {
            return false;
        }
    }
    
    // Call memory manager's init function with aligned address and size
    int result = memMgr->initBuffer(this->m_alignedSendPtr, this->m_sendSize); // vtable[0x50]
    this->m_sendBufferHandle = result;
    
    if (result >= 0)
    {
        // Validate handle
        bool isValid = memMgr->isValidHandle(result, 0); // vtable[0x6c]
        if (isValid)
        {
            bool extraCheck = FUN_005e80f0();   // some validation function
            if (extraCheck)
            {
                bResult = true;
            }
        }
        // Cleanup / finalize
        FUN_005dbc10(this->m_sendBufferHandle, this->m_sendSize);
    }
    
    return bResult;
}