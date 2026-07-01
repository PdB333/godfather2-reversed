// FUNC_NAME: Entity::scalarDeletingDestructor
Entity* __thiscall Entity::scalarDeletingDestructor(Entity* this, byte deallocFlag) {
    // Set vtable to base class to prevent virtual calls during destruction
    this->vtable = &Entity_base_vtable; // 0x00d7c910
    // Call base class destructor (or virtual destructor implementation)
    Entity::baseDestructor(); // FUN_008cdd20
    // If deallocation flag is set, free memory via custom allocator
    if ((deallocFlag & 1) != 0) {
        // Get the allocator object (likely a singleton or global)
        Allocator* allocator = (Allocator*)FUN_009c8f80();
        // Call operator delete with size 0xE0 (224 bytes)
        allocator->deallocate(this, 0xE0);
    }
    return this;
}