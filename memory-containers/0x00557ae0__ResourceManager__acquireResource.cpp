// FUNC_NAME: ResourceManager::acquireResource
// Address: 0x00557ae0
// Role: Allocates a resource slot, decrements refcount of a looked-up resource, copies data pointer from a container, marks manager as loaded.

// Reconstructed structures (offsets relative to pointer)
// ResourceSlot: size 0x70? Only offsets 0x00 (vtable), 0x04 (size), 0x06 (refCount), 0x08 (data) used
// ResourceContainer: +0x08 = keys array (int*), +0x0C = count, +0x5C = values array (void**), +0x60 = capacity
// This class has a byte at +0x48 (m_loadComplete)

void ResourceManager::acquireResource(
    ResourceDescriptor* pDesc,          // param_2: resource descriptor with hash at +0x10
    ResourceContainer* pContainer,      // param_3: container holding resource mappings
    void* param4,                       // passed through to registration
    void* param5                        // passed through to registration
) {
    // Begin profiling
    FUN_00559d40(); // profileBegin

    // Get thread-local storage (e.g., app context)
    TlsGetValue(DAT_01139810);

    // Allocate a new resource slot (0x70 bytes, tag 0x27)
    ResourceSlot* newSlot = (ResourceSlot*)FUN_00aa2680(0x70, 0x27);
    newSlot->size = 0x70;

    // Look up an existing resource slot by descriptor hash + global table
    ResourceSlot* existingSlot = (ResourceSlot*)FUN_00a6be50(
        *(int*)((uint8_t*)pDesc + 0x10),
        &DAT_011397d0
    );

    // Register the resource with some system (e.g., tell about loading)
    FUN_00556ab0(pDesc, pContainer, param4, param5, -1);

    // Decrement refcount of the existing slot; if it reaches 0, call destructor
    if (existingSlot->size != 0) {
        existingSlot->refCount--;
        if (existingSlot->refCount == 0) {
            // Call vtable function at offset 0 with argument 1 (likely release/destroy)
            ((void (*)(int))existingSlot->vtable)(1);
        }
    }

    // Now look in the container for a matching descriptor
    int* keysArray = (int*)((uint8_t*)pContainer + 8);   // +0x08: pointer to array of resource descriptor pointers
    int count = *(int*)((uint8_t*)pContainer + 0x0C);     // +0x0C: number of entries
    int capacity = *(int*)((uint8_t*)pContainer + 0x60);  // +0x60: max capacity of arrays

    if (keysArray == 0) {
        *(uint8_t*)(this + 0x48) = 1; // m_loadComplete = true
        return;
    }
    if (capacity < 1) {
        *(uint8_t*)(this + 0x48) = 1;
        return;
    }

    for (int i = 0; i < count; i++) {
        if (keysArray[i] == (int)pDesc) { // Compare descriptor pointers
            if (i >= 0 && i < capacity) {
                // Copy the data pointer from the container's values array to the existing slot
                void** valuesArray = (void**)((uint8_t*)pContainer + 0x5C); // +0x5C: pointer to array of data pointers
                existingSlot->data = valuesArray[i];
                goto SetLoaded;
            }
            break;
        }
    }

SetLoaded:
    *(uint8_t*)(this + 0x48) = 1; // m_loadComplete = true
}