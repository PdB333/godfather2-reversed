// FUNC_NAME: ResourceManager::resolveResource
// Function address: 0x006bf050
// Role: Resolves a resource handle (array pointer + index). Loads/initializes resource if not already loaded,
// using a global singleton manager. Returns pointer to resource object. Handles streaming/loading flags.

int __thiscall ResourceManager::resolveResource(int *handle)
{
    int resourcePtr;
    int index;
    int *singleton;

    index = handle[1];                       // handle->index (1-based)
    resourcePtr = handle[0][index - 1];      // dereference handle->array[index-1]

    singleton = (int *)getGlobalSingleton(); // FUN_00791300 – e.g., StreamManager or FileSystemManager
    if (singleton == nullptr) {
        // No global manager; check if resource already loading/loaded
        if ((*(uint *)(resourcePtr + 0x5c) & 0x60000) != 0) { // flags: streaming active?
            *(uint *)(resourcePtr + 0x5c) |= 0x40000000;      // mark as loaded/ready
            return 0;
        }
    }
    else {
        // Singleton exists; check its internal ready flag (bit 25 at offset 0x1F58)
        if (((uint)singleton[0x7d6] >> 0x19 & 1) == 0) {
            // Not ready yet – call virtual method to initiate load
            (*(void (**)(int, int, int))(*singleton + 0x288))(2, 0, 0);
            return 0;
        }
        // Singleton ready – set resource path from singleton's internal field
        setResourcePath(singleton + 0xf); // FUN_004088c0: e.g., copies base path to some buffer
    }

    if (resourcePtr != 0) {
        releaseHandleIndex(index - 1); // FUN_006be9f0: decrement reference or index lock
        releaseManager(this);          // FUN_00791350: unlock/release the manager
        finalizeLoad();                // FUN_006bec10: post-load cleanup
    }

    return resourcePtr; // return pointer to resource (may be null if failed)
}