// FUNC_NAME: ResourceHandle::release
// Address: 0x005c08f0
// This method releases a resource handle, decrementing reference counts and clearing internal pointers.

void __thiscall ResourceHandle::release(ResourceHandle* this)
{
    bool bShuttingDown; // From global flag DAT_01205664

    // Clear owned and ref count fields
    this->refCount = 0;   // +0xc
    this->pOwner = 0;     // +0x8

    // If an inner resource pointer exists, release it via its vtable
    if (this->pResource != nullptr) // +0x4
    {
        // Dereference global table at DAT_012234ec to get the resource manager's vtable
        // Then call the second virtual method (index 1) on the resource object with argument 0
        // Typically this is a Release() or DecrementRef() call
        (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this->pResource, 0);
    }

    bShuttingDown = (DAT_01205664 == 0); // Check if engine is not shutting down

    // Clear the resource pointer
    this->pResource = 0; // +0x4

    if (bShuttingDown)
    {
        // Global shutdown/cleanup routine (e.g., decrement global resource count)
        FUN_005c39d0();
    }

    // Finalize this handle (e.g., remove from global list)
    FUN_005c3c70(this);

    return;
}