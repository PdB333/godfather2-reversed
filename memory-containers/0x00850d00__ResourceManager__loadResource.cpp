// FUNC_NAME: ResourceManager::loadResource
// Address: 0x00850d00
// Role: Lazy-loads a resource (e.g., stream, asset) identified by param_3.
// If not yet loaded (*param_2 == 0), allocates memory, constructs the resource,
// and posts a completion message. If already loaded, calls a reload/update function.

void ResourceManager::loadResource(void* thisPtr, int* outHandle, int resourceId, int flags)
{
    int uVar1; // result from allocateResource
    int iVar2; // allocated memory block

    if (*outHandle == 0) {
        // Resource not loaded yet – allocate and construct
        uVar1 = allocateResource(flags, 0x1f, 0); // 0x1f = resource type? 0 = flags?
        TlsGetValue(DAT_01139810); // Thread-local storage access (likely debug/context)
        iVar2 = allocateMemory(0xd0, 0x31); // Allocate 0xd0 bytes, tag 0x31
        *(short*)(iVar2 + 4) = 0xd0; // Store allocation size at offset +4 (header)
        *outHandle = constructResource(resourceId, uVar1); // Build resource object
        if (*outHandle != 0) {
            onResourceLoaded(); // Notify success
            postMessage(0x2001, thisPtr, 0); // Send "resource loaded" message (0x2001)
        }
        return;
    }
    // Resource already loaded – perform reload/update
    reloadResource(resourceId);
}