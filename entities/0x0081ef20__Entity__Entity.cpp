// FUNC_NAME: Entity::Entity
// Reconstructed constructor for a game object (likely Entity or similar) at 0x0081ef20
// Uses a base class constructor and optionally allocates memory via a global allocator.
undefined4 __thiscall Entity::Entity(Entity* this, byte constructorFlags) {
    // Call base class constructor (likely Object or SimBase)
    baseClassConstructor(this);  // FUN_0081e710

    // If bit 0 of constructorFlags is set, allocate a new block of memory
    if ((constructorFlags & 1) != 0) {
        // Get global memory manager allocator (returns pointer to allocator object)
        MemoryAllocator* allocator = (MemoryAllocator*)getMemoryAllocator();  // FUN_009c8f80
        // Call allocate method (second virtual function, offset +0x4 from vtable)
        // Parameters: this pointer (the object being constructed?) and size 0x130
        allocator->allocate(this, 0x130);  // (**(code **)(*allocator + 4))(this, 0x130)
    }
    return (undefined4)this;
}