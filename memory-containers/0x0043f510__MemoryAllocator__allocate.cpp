// FUNC_NAME: MemoryAllocator::allocate

void __thiscall MemoryAllocator::allocate(uint* this, uint* source)
{
    uint* bufferPtr;
    // Save return address (used later as a value to store)
    uint savedRetAddr = unaff_retaddr;
    
    // Get the auxiliary buffer pointer from this->auxBuffer (offset +0x04)
    bufferPtr = (uint*)this[1];
    
    // If the auxiliary buffer is null, use a local stack buffer
    if ((undefined1*)this[1] == (undefined1*)0x0) {
        uint localBuffer[3] = {0, 0, 0}; // 12 bytes: local_c, local_8, local_4
        bufferPtr = localBuffer;
    }
    
    // Call the virtual allocate method (vtable[0]) with size 12 and the buffer pointer
    // vtable is at *this, first entry is the allocator function
    // The return value is a pointer to the newly allocated memory
    uint* newMem = (uint*)(*(code*)**(undefined4**)*this)(12, bufferPtr);
    
    // If the allocation succeeded, copy the data from the source parameter
    if (newMem != (uint*)0x0) {
        *newMem = local_4;           // +0x00: copy first word from stack buffer
    }
    if (newMem + 1 != (uint*)0x0) {
        newMem[1] = savedRetAddr;    // +0x04: copy return address as a value
    }
    if (newMem + 2 != (uint*)0x0) {
        newMem[2] = *source;         // +0x08: copy first word from source parameter
    }
    
    return;
}