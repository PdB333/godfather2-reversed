// FUNC_NAME: Entity::scalarDeletingDestructor

undefined4 __thiscall Entity::scalarDeletingDestructor(Entity* this, byte flag) {
    // 0x008276f0: Base class destructor (non-deleting)
    baseDestructor();
    
    // If bit 0 of flag is set, deallocate memory (operator delete)
    if ((flag & 1) != 0) {
        // 0x009c8eb0: Memory deallocation (likely operator delete)
        memoryFree(this);
    }
    
    return this;
}