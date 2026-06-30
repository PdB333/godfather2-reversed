// FUNC_NAME: ResourceCache::getOrCreateResource
// Address: 0x0069be40
// Role: Acquires a cached resource identified by a key; if not found and a global slot index is valid, creates a new object, then returns this.

#include <cstdint>

// Global variables (from data references)
extern int32_t g_slotIndex;               // DAT_00e506ac
extern uint8_t* g_slotArrayStart;          // DAT_01129f8c
extern uint8_t* g_slotArrayEnd;            // DAT_01129f90

// Forward declarations of internal helpers
bool getCachedResource(uint32_t key, int32_t** outObject);          // FUN_00699b70
void releaseCacheEntry(int32_t* object);                            // FUN_004d3b50
void acquireObjectLock(uint32_t key);                               // FUN_004d3bc0
bool allocateNewObject(int32_t** newObject);                        // FUN_0069b380
void releaseObjectLock(uint32_t key);                               // FUN_004d3e20

// Function pointer types (potentially from a vtable or callback)
typedef void (*DestructorFunc)(int32_t*);
typedef void (*ReleaseFunc)(int32_t*);

int32_t* ResourceCache::getOrCreateResource(uint32_t key, int32_t* output)
{
    int32_t* cachedObject[3] = {nullptr, nullptr, nullptr};
    DestructorFunc destroyCallback = nullptr;   // local_14 (uninitialized in original)
    int32_t* newObject[3];                      // local_10
    DestructorFunc initCallback = nullptr;      // local_4 (uninitialized in original)

    bool found = getCachedResource(key, cachedObject);
    if (!found)
    {
        // Check if the global slot index is within the valid range of the static array
        int32_t slotCount = (g_slotArrayEnd - g_slotArrayStart) >> 2; // number of slots
        if (g_slotIndex >= 0 && g_slotIndex < slotCount)
        {
            acquireObjectLock(key);
            bool allocated = allocateNewObject(newObject);
            releaseObjectLock(key);   // param_3 -> key (original usage unclear)

            if (allocated && newObject[0] != nullptr)
            {
                // Note: initCallback is uninitialized; original code calls it unconditionally
                // This likely indicates a missing assignment elsewhere (e.g., from a global or register)
                if (initCallback != nullptr)
                    initCallback(newObject[0]);
            }
        }
        releaseCacheEntry(output); // param_3 passed as output? original uses param_3 here
    }
    else
    {
        releaseCacheEntry(cachedObject); // release the found cached object
    }

    // Cleanup: if cachedObject[0] is non-null, call its release callback
    if (cachedObject[0] != nullptr)
    {
        // Note: destroyCallback is uninitialized; same missing initialization issue
        if (destroyCallback != nullptr)
            destroyCallback(cachedObject[0]);
    }

    return this; // param_1
}