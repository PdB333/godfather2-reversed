// FUNC_NAME: ResourceManager::getOrCreateResource
// Function address: 0x0069bcc0
// Role: Retrieves a resource by key, with caching and fallback. If not cached, checks a global resource array and creates if valid.

#include <cstdint>

// Forward declarations of called functions
bool tryGetCachedValue(uint32_t key, uint32_t* outValue); // FUN_00699970
void prepareResource(uint32_t key); // FUN_004d3bc0
bool createResource(uint32_t key, ResourceResult* result); // FUN_0069b4b0

// Global resource array bounds (from data)
extern int32_t g_resourceIndex; // DAT_00e506ac
extern uint32_t* g_resourceArrayStart; // DAT_01129f8c
extern uint32_t* g_resourceArrayEnd;   // DAT_01129f90

// Struct to hold result of resource creation
struct ResourceResult {
    int32_t value;       // local_10[0]
    void (*callback)(int32_t); // local_4 (function pointer)
};

uint32_t ResourceManager::getOrCreateResource(uint32_t key, uint32_t defaultValue) {
    uint32_t cachedValue;
    
    // Try to get from cache
    if (tryGetCachedValue(key, &cachedValue)) {
        return cachedValue;
    }
    
    // Check if the global resource index is valid (within array bounds)
    int32_t arrayCount = (g_resourceArrayEnd - g_resourceArrayStart) >> 2; // element count
    if (g_resourceIndex >= 0 && g_resourceIndex < arrayCount) {
        prepareResource(key);
        
        ResourceResult result;
        if (createResource(key, &result)) {
            // If creation succeeded, call the callback with the result value
            if (result.callback != nullptr) {
                result.callback(result.value);
            }
        }
    }
    
    return defaultValue;
}