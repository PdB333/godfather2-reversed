// FUNC_NAME: ControllerManager::ControllerManager
void __thiscall ControllerManager::ControllerManager(void *this, void *vtable) {
    // vtable passed in EAX, this in ESI
    // +0x00: vtable
    *(int *)this = (int)vtable;
    // +0x04: sub-object pointer (set later)
    // +0x08 to +0x28: zeroed fields (likely controller states or counters)
    for (int i = 2; i < 10; i++) {
        ((int *)this)[i] = 0;
    }
    // +0x28: single byte zeroed
    *(char *)((int)this + 0x28) = 0;

    // Allocate a sub-object of size 0x14 (20 bytes) – likely a memory pool or controller array
    void *sub = (void *)FUN_009c8e50(0x14);
    if (sub) {
        struct PoolParams {
            int unknown; // 2 – maybe element size?
            int count;   // 0x10 (16) – number of slots
            int flags;   // 0
        } params = {2, 0x10, 0};

        // Get global memory allocator (vtable-based)
        int *allocator = (int *)FUN_009c8f80();
        // Create pool/handle from allocator
        int handle = FUN_004265d0(&params, allocator);
        ((int *)sub)[3] = handle;
        ((int *)sub)[4] = (int)allocator;

        // Call third virtual method on allocator (likely initPool or allocate)
        (*(void (**)(void))(*allocator + 8))();

        // Zero out first three fields of sub-object (offset +0x00, +0x04, +0x08)
        ((int *)sub)[0] = 0;
        ((int *)sub)[1] = 0;
        ((int *)sub)[2] = 0;

        // Store sub-object at this+0x04
        ((int *)this)[1] = (int)sub;
    } else {
        // Allocation failed – set sub-object pointer to null
        ((int *)this)[1] = 0;
    }
}