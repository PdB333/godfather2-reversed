// FUNC_NAME: SimManager::SimManager
undefined4* __thiscall SimManager::SimManager(undefined4* this, byte allocateFlag)
{
    int* allocator;
    
    // Set vtable pointers for the two base classes (multiple inheritance)
    *this = &g_vtable_SimManager;               // +0x00: primary vtable
    this[2] = &g_vtable_SimManagerInterface;    // +0x08: secondary vtable (interface)
    
    // Release any existing sub-objects at offsets 0xC0 and 0xC8
    if (this[0x30] != 0) {                      // +0xC0: pointer to child object
        releaseSubObject((undefined4*)(this + 0x30));
    }
    if (this[0x32] != 0) {                      // +0xC8: pointer to another child object
        releaseSubObject((undefined4*)(this + 0x32));
    }
    
    // Perform static initialization (singleton or global data)
    initializeStaticData();
    
    // If the allocation flag is set, allocate memory for this manager
    if ((allocateFlag & 1) != 0) {
        allocator = (int*)getMemoryAllocator();   // Returns pointer to global allocator
        // Call allocator's placement new/member function with this and size
        (*(code**)(*allocator + 4))(this, 0x2e0); // Size 0x2E0 (736 bytes)
    }
    
    return this;
}