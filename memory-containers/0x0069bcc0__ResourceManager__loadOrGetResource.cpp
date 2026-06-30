// FUNC_NAME: ResourceManager::loadOrGetResource

// Address: 0x0069bcc0
// Role: Attempts to find an existing resource by ID; if not found and within global resource slot limit, 
//       creates a new one and calls a post-initialization function on it.
// Returns resource handle on success, otherwise returns the original resourceId as a fallback.

struct ResourceSlotResult {
    int handle;        // +0x00
    int unknown;       // +0x04
    void (*initFunc)(int); // +0x08
};

// Global resource slot tracking
extern int g_resourceCount;                    // DAT_00e506ac
extern int g_resourceTableStart;               // DAT_01129f8c
extern int g_resourceTableEnd;                 // DAT_01129f90

int ResourceManager::loadOrGetResource(int resourceId) {
    int foundHandle;
    
    // Try to locate an already loaded resource
    if (this->tryFindResource(resourceId, &foundHandle)) {
        return foundHandle;
    }
    
    int resourceCount = g_resourceCount;
    int maxSlots = (g_resourceTableEnd - g_resourceTableStart) >> 2; // number of slots available
    if (resourceCount >= 0 && resourceCount < maxSlots) {
        // Initialize/load the resource data
        this->loadResourceData(resourceId); // FUN_004d3bc0
        
        // Allocate a new resource slot; fills a ResourceSlotResult struct
        ResourceSlotResult slotResult;
        this->allocateResourceSlot(&slotResult, resourceId); // FUN_0069b4b0
        
        if (slotResult.handle != 0 && slotResult.initFunc != nullptr) {
            slotResult.initFunc(slotResult.handle);
        }
    }
    
    return resourceId;
}