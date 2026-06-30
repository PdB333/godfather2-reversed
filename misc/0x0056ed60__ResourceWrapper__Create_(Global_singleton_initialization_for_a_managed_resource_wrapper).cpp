// FUNC_NAME: ResourceWrapper::Create (Global singleton initialization for a managed resource wrapper)
// Address: 0x0056ed60
// Role: Allocates a ResourceWrapper object, calls a virtual function on the passed parent object to obtain a resource handle, and stores the wrapper in a global pointer.

void ResourceWrapper::Create(void* parentObject, int initParam)
{
    // Custom allocator for 0x14 bytes (ResourceWrapper size: 5 dwords)
    ResourceWrapper* pWrapper = (ResourceWrapper*)operatorNew(0x14); // FUN_009c8e50

    if (pWrapper != nullptr) {
        // Fill structure fields:
        pWrapper->m_parentObject = parentObject;   // +0x00: pointer to the parent (e.g., a factory or manager)
        pWrapper->m_state = 0;                     // +0x04: initial state (0 = uninitialized/ready)
        pWrapper->m_param = initParam;             // +0x10: copy of the parameter passed in

        // Prepare descriptor for resource creation: {requestType=2, size=0x10, flags=0}
        int descriptor[3] = { 2, 0x10, 0 };

        // Call virtual function on parent object to create a resource handle.
        // The vtable is at *parentObject; the first function is used (likely some "createResource" method).
        void* (*createFunc)(void*, int, int*) = *(void*(**)(void*, int, int*))parentObject;
        void* resourceHandle = createFunc(parentObject, initParam, descriptor);

        // Store handle in two fields (possibly start and current pointer or primary and backup)
        pWrapper->m_handleLo = resourceHandle;     // +0x08
        pWrapper->m_handleHi = resourceHandle;     // +0x0C (duplicate)

        // Set global singleton pointer
        g_pResourceWrapper = pWrapper;
    }
    else {
        g_pResourceWrapper = nullptr;
    }
}

// Global storage at 0x01205560
ResourceWrapper* g_pResourceWrapper = nullptr;