// FUNC_NAME: ObjectPool::acquireObject(uint id)
// 0x0066f360
// Acquires an object matching the given id from the pool.
// Returns a pointer to the object's data (the payload of the slot), or nullptr if not available.
// Uses a free list per slot and a fallback factory for creation.
void* ObjectPool::acquireObject(uint id) {
    void* result = nullptr;

    // Iterate over all slots in the pool
    for (int i = 0; i < slotCount; i++) {
        // If we already have a hit, return it early (should not happen normally)
        if (result != nullptr) {
            return result;
        }

        Slot* slot = slots[i];  // pointer to slot structure
        // Check if slot's id matches (condition param_1 <= slot->id) and slot is not empty
        if (id <= slot->id && slot->refCount != 0) {
            // Try to pop from the free list first
            void* node = slot->freeList;
            if (node == nullptr) {
                // Free list empty, need to create a new node via factory
                if (slot->factory == nullptr) {
                    result = nullptr;
                } else {
                    // Call factory->create(slot->id, slot->data)
                    // vtable+4 is typically the create method
                    result = slot->factory->vtable->create(slot->id, slot->data);
                }
            } else {
                // Pop from free list
                result = node;
                // Update free list to next node (first field of node is next pointer)
                slot->freeList = *(void**)node;
                // Decrement reference count
                slot->refCount--;
                // Update min ref count if necessary
                if (slot->refCount < slot->minRefCount) {
                    slot->minRefCount = slot->refCount;
                }
            }
        }
    }

    // If no slot matched, try the fallback factory
    if (result != nullptr) {
        return result;
    }

    if (fallbackFactory == nullptr) {
        return nullptr;
    }

    // Call fallbackFactory->create(id, 0x10)
    // Second argument 0x10 might be a size or type constant
    result = fallbackFactory->vtable->create(id, 0x10);
    return result;
}