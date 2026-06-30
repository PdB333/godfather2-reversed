// FUNC_NAME: ResourceManager::loadAndRegisterResource
int ResourceManager::loadAndRegisterResource(int resourceType, int flags, int extraData, int callback, int slotHint, int unused, int resourceId)
{
    int handle;
    int slotIndex;

    // Allocate a resource object (possibly load from file or instantiate)
    handle = this->allocateResource(resourceType, flags, extraData, callback, resourceId); // FUN_00606c80

    // Try to find an available slot in the resource table for this handle
    slotIndex = this->findFreeSlot(handle, slotHint); // FUN_00606ac0

    if (slotIndex == -1)
    {
        // No slot available; release the allocated resource and return failure
        this->releaseResource(handle, 0); // FUN_006065a0
        return -1;
    }

    // Success: return the handle (slot registration completed externally or later)
    return handle;
}