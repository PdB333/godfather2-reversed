// FUNC_NAME: MemoryAllocator::allocateAndCopy
void __thiscall MemoryAllocator::allocateAndCopy(void* this, void* source, size_t size, int flags, void* resultOut)
{
    void* tempBuffer[4]; // 16-byte buffer on stack
    void** tempPtr;      // pointer to tempBuffer or an allocated block
    
    tempPtr = tempBuffer; // initially point to stack buffer
    memset(tempBuffer, 0, sizeof(tempBuffer)); // clear the 16-byte area
    
    // First function likely copies or transforms source data into tempBuffer format
    FUN_005ad100(source, size, flags, tempBuffer);
    
    // This function performs the actual allocation and copy using the processed data
    FUN_005ad380(this, tempBuffer, resultOut);
    
    // Cleanup if tempPtr was replaced with heap allocation (alignment/memory management pattern)
    if (tempPtr != tempBuffer && tempPtr != nullptr) {
        (*DAT_0119caf4)(tempPtr); // likely an aligned free function
    }
}