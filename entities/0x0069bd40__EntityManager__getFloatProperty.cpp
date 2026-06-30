// FUNC_NAME: EntityManager::getFloatProperty
// Function address: 0x0069bd40
// Role: Retrieves a float property for an entity, first checking a cache.
// If cached value exists, returns it directly. Otherwise, if a valid
// global index into an array of entities is set, triggers an update
// and builds a callback structure to potentially call a function.

// Global state used by this function
extern int g_entityIndex;              // DAT_00e506ac
extern void* g_entityArrayBase;        // DAT_01129f8c
extern void* g_entityArrayEnd;         // DAT_01129f90
extern int g_entityArrayCount;         // (g_entityArrayEnd - g_entityArrayBase) >> 2

// Structure returned by buildList – contains entity pointer and callback
struct CallbackData {
    int entityId;        // +0x00: first field (used as check and argument)
    int padding1;        // +0x04
    int padding2;        // +0x08
    void (*callback)(void*); // +0x0C: function pointer to call
};

float EntityManager::getFloatProperty(float defaultVal)
{
    float cached;

    // Attempt to get a cached float value for this entity
    if (this->getCachedFloat(&cached)) {
        return cached;
    }

    // If global entity index is within valid range, perform update and callback
    if (g_entityIndex >= 0 && g_entityIndex < g_entityArrayCount) {
        // Perform update on this entity
        this->doUpdate();

        // Build callback data with the default value as parameter
        CallbackData cbData;
        buildList(&cbData, defaultVal);

        // If the first field is non-zero, call the function pointer with it
        if (cbData.entityId != 0) {
            cbData.callback((void*)cbData.entityId);
        }
    }

    // Return the default value if no cached value was found
    return defaultVal;
}