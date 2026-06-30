// FUNC_NAME: MemoryPool::deallocateNode

void MemoryPool::deallocateNode()
{
    // Offset +0x4: pointer to the child allocation
    int* childPtr = *reinterpret_cast<int**>(reinterpret_cast<uint8_t*>(this) + 0x4);
    if (childPtr != nullptr)
    {
        // vtable is stored 4 bytes before the child data
        int* vtable = childPtr - 1;
        // Deallocate the child block with size 0x30, vtable value, and a cleanup callback
        MemorySystem::blockDeallocate(childPtr, 0x30, *vtable, &cleanupCallback);
        // Destroy the child object (calls virtual destructor)
        MemorySystem::objectDestroy(vtable);
    }
    // Free the container memory
    MemorySystem::freeContainer(this);
}