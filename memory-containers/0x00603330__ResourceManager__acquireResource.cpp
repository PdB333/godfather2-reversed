// FUNC_NAME: ResourceManager::acquireResource
// Function address: 0x00603330
// Role: Acquires or creates a resource of a given type, and returns it through a handle structure.
// The handle struct (param_2) is a resource handle with fields:
//   +0: pointer to resource data (or null if empty)
//   +4: size (e.g., data size)
//   +8: capacity (e.g., allocated size)
//  +12: destructor function pointer (called to release the resource when replacing)

struct ResourceHandle {
    void* data;           // +0
    uint32_t size;        // +4
    uint32_t capacity;    // +8
    void (*destructor)(void*); // +12
};

// Forward declarations of callees
// 0x006039d0: internalGetOrCreateResource - checks cache/creates, returns success, resource id, and flag
bool ResourceManager::internalGetOrCreateResource(uint32_t resourceType, uint32_t& outResourceId, bool& outIsNewAllocation);
// 0x004ddaf0: assignResourceHandle - sets up the handle with the resource
void ResourceManager::assignResourceHandle(uint32_t resourceId, ResourceHandle* handle);
// 0x004d3d90: releaseResource - releases a temporary resource reference
void ResourceManager::releaseResource(uint32_t resourceId);

void ResourceManager::acquireResource(uint32_t resourceType, ResourceHandle* handle) {
    uint32_t resourceId = 0;
    bool isNewAllocation = false;

    bool success = internalGetOrCreateResource(resourceType, resourceId, isNewAllocation);
    
    if (!success) {
        // Resource creation failed – release any previous handle content
        if (handle->data != nullptr) {
            handle->destructor(handle->data);
        }
        handle->data = nullptr;
        handle->capacity = 0;
        handle->size = 0;
        return;
    }

    if (isNewAllocation) {
        // We got a new resource that was freshly allocated – replace handle
        if (handle->data != nullptr) {
            handle->destructor(handle->data);
        }
        handle->data = nullptr;
        handle->capacity = 0;
        handle->size = 0;
        assignResourceHandle(resourceId, handle);
        return;
    }

    // Resource already existed in cache – just release the temporary reference
    releaseResource(resourceId);
    return;
}