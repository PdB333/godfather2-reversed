// FUNC_NAME: ResourceManager::getResourceHandle
uint __thiscall ResourceManager::getResourceHandle(uint param_1, int resourceId)
{
    int platformId;
    uint handle;
    
    platformId = getPlatformId();
    if (platformId != 0x637b907) { // Not PC platform?
        int index = getResourceIndex(resourceId);
        if (index != 0) {
            handle = getResourceFromIndex(index);
            return handle;
        }
        return 0;
    }
    // PC platform path
    handle = getResourceDirect(resourceId);
    if (handle != 0xFFFFFFFF) {
        this->lastHandle = handle; // +0x130 cached handle
        handle = getResourceManagerSingleton(0x637b907);
        return handle;
    }
    *(int *)(this + 0x130) = -1; // lastHandle = -1
    return handle & 0xFFFFFF00; // mask out low byte (error code?)
}