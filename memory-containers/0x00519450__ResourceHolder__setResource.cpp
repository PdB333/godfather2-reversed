// FUNC_NAME: ResourceHolder::setResource
void ResourceHolder::setResource(int resourceId)
{
    int oldResourceId;
    int *freeListEntry;
    int oldPtr;
    int baseAddr;

    // Save original resource ID
    oldResourceId = resourceId;

    // Clear loaded flag if set
    if (this->loadedFlag != 0) {
        this->loadedFlag = 0; // +0x1c
    }

    // If there is an existing resource and the ID is different
    if (this->resourcePtr != 0) { // +0x14
        if (this->currentResourceId != resourceId) { // +0x10
            oldPtr = this->resourcePtr;
            if (oldPtr != 0) {
                // Add old resource pointer to global free list
                freeListEntry = (int *)(gMemPool + 0x14); // DAT_01206880 + 0x14
                **(int **)freeListEntry = (int)&PTR_LAB_01123be8; // magic constant
                *freeListEntry = *freeListEntry + 4;
                *(int *)*freeListEntry = oldPtr;
                *freeListEntry = *freeListEntry + 4;
                this->resourcePtr = 0; // +0x14
                this->resourceSize = 0; // +0x18
            }
            this->resourcePtr = 0;
            this->resourceSize = 0;
        }
        if (this->resourcePtr != 0) goto LAB_005194cd;
    }

    resourceId = 0;
    if (oldResourceId == 0) {
        baseAddr = 0;
    }
    else {
        // Load resource: function modifies resourceId to become pointer
        FUN_00485650(&resourceId);
        baseAddr = oldResourceId;
    }
    this->resourcePtr = resourceId; // +0x14
    this->resourceSize = baseAddr;  // +0x18 (holds original ID? seems odd)

    if (resourceId == 0) {
        this->currentResourceId = 0; // +0x10
        return;
    }

LAB_005194cd:
    this->currentResourceId = oldResourceId; // +0x10

    // Compute adjusted pointer using TLS offset?
    if (this->resourcePtr != 0) {
        // Gets TLS base and adds resource pointer
        baseAddr = *(int *)(**(int **)(__readfsdword(0x2c) + 8) + this->resourcePtr);
    }
    else {
        baseAddr = 0;
    }

    // Call virtual callback with adjusted pointer and resource ID
    (this->resourceInterface->onResourceChanged)(baseAddr, oldResourceId); // vtable+0x14
    return;
}