// FUNC_NAME: ResourceManager::releaseResource
void __thiscall ResourceManager::releaseResource(uint resourceIndex)
{
    // Access the resource array at offset +4 from this
    ResourceEntry* entryArray = *(ResourceEntry**)((uintptr_t)this + 4);
    
    // Validate index: must not be 0xFFFFFFFF and less than 64 (max slots)
    if ((resourceIndex != 0xFFFFFFFF) && (resourceIndex < 0x40)) {
        ResourceEntry* entry = &entryArray[resourceIndex];
        int refCount = entry->refCount; // +0x04
        
        if (refCount != 0) {
            refCount--;
            entry->refCount = refCount; // Decrement reference count
            
            // If ref count reached 0 and no pending operation (someFlag == 0), free the handle
            if ((refCount == 0) && (entry->someFlag == 0)) {
                entry->handle = 0xFFFFFFFF; // +0x00, mark as invalid handle
            }
        }
    }
}