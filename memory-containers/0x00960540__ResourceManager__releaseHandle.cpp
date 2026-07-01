// FUNC_NAME: ResourceManager::releaseHandle
// Address: 0x00960540
// Releases a resource handle by first decrementing a global reference count and then freeing the handle itself.
// param_1 (this) - ResourceManager instance (unused? may be used in non-inlined code)
// param_2 - handle/index to the resource to free

void ResourceManager::releaseHandle(int resourceHandle)
{
    if (resourceHandle != 0) {
        // Decrement global reference count or perform some shared cleanup
        ResourceManager::decrementGlobalRefCount();  // FUN_009823b0
        // Release the specific handle (e.g., free memory, close handle)
        this->freeHandle(resourceHandle);            // FUN_009c8eb0
    }
}