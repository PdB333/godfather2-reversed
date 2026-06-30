// FUNC_NAME: ObjectFactory::allocateObject
// This function allocates a large memory block (0x4d38 bytes) and initializes an object pointer at offset 0x1c.
void __fastcall ObjectFactory::allocateObject(ObjectFactory* thisFactory)
{
    // Global memory system initialization (maybe per-frame or per-scene)
    MemorySystem::init();

    // Allocation parameters (likely heap type, alignment, flags)
    HeapAllocParams allocParams;
    allocParams.field0 = 2;      // +0x00: possibly heap index or type
    allocParams.field1 = 0x10;   // +0x04: alignment or pool size
    allocParams.field2 = 0;      // +0x08: flags

    // Attempt to allocate a block of 0x4d38 bytes
    void* allocatedBlock = HeapSystem::allocate(0x4d38, &allocParams);
    if (allocatedBlock != nullptr)
    {
        // Allocation succeeded; create the actual object and store its pointer
        thisFactory->m_objectPointer = ObjectFactory::createObject(thisFactory); // FUN_0067fd50
        return;
    }

    // Allocation failed; clear the pointer
    thisFactory->m_objectPointer = nullptr;
}