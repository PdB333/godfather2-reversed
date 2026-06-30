// FUNC_NAME: ResourceManager::reloadResource
void ResourceManager::reloadResource()
{
    this->isLoaded = false; // +0x144

    if (this->resourcePtr != 0) // +0x140
    {
        resourceFree(this->resourcePtr);
        this->resourcePtr = 0;      // +0x140
        this->resourceHandle = 0;   // +0x13c
    }

    unsigned int handle = resourceFindHandle(0x5beea32a); // hash for resource name
    this->resourceHandle = handle; // +0x13c

    void* ptr = resourceLockPointer(handle);
    this->resourcePtr = ptr; // +0x140

    if (ptr != 0)
    {
        resourceAttach(0x5beea32a, ptr, handle);
        this->isLoaded = true; // +0x144
    }
}