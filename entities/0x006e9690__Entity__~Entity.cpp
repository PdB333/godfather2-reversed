// FUNC_NAME: Entity::~Entity
// Destructor for a game entity (address 0x006e9690).
// Performs cleanup of components and memory, then sets vtable to base class
// and resets a global flag.

void __fastcall Entity::~Entity()
{
    // Set vtable pointer to derived class vtable (entry point)
    this->m_vtable = (void**)&g_vtableDerived; // PTR_FUN_00d5fd04

    // Possibly set another data pointer (offset +0x04)
    this->m_someData = &g_unknownData; // PTR_LAB_00d5fcf4

    // Call virtual function at offset 0x0C on component (+0x14)
    // This is likely a cleanup/shutdown method on the component
    Component* comp = *(Component**)((char*)this + 0x14);
    if (comp)
    {
        void** compVtable = *(void***)comp;
        void (*cleanupFunc)(Component*) = (void (*)(Component*))compVtable[3]; // index 3 = offset 0x0C
        cleanupFunc(comp);
    }

    // Call allocator release for buffer1 (+0x18) with flag 0
    Allocator* alloc = *(Allocator**)((char*)this + 0x28);
    if (alloc)
    {
        void** allocVtable = *(void***)alloc;
        void (*releaseFunc)(Allocator*, void*, int) = (void (*)(Allocator*, void*, int))allocVtable[1]; // index 1 = offset 0x04
        void* buffer1 = *(void**)((char*)this + 0x18);
        if (buffer1)
        {
            releaseFunc(alloc, buffer1, 0);
        }

        // Release optional buffer2 (+0x24)
        void* buffer2 = *(void**)((char*)this + 0x24);
        if (buffer2)
        {
            releaseFunc(alloc, buffer2, 0);
        }

        // Call virtual function at offset 0x0C on allocator (likely finalize/flush)
        void (*flushFunc)(Allocator*) = (void (*)(Allocator*))allocVtable[3];
        flushFunc(alloc);
    }

    // Global memory/service cleanup call
    FUN_004083d0(); // likely MemManager::cleanup

    // Set vtable to base class vtable (prevent virtual calls during destruction)
    this->m_vtable = (void**)&g_vtableBase; // PTR_LAB_00d5fcb8

    // Reset global flag
    DAT_011298cc = 0;

    return;
}