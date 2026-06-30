// FUNC_NAME: ResourceManager::loadResource
void ResourceManager::loadResource(void* pContext) {
    int resourceIndex = 0; // local_18
    bool bFound = findResourceIndex(this, &resourceIndex); // FUN_00605b80
    if (bFound) {
        // Determine if debug flag is set to decide allocation behavior
        int allocSize;
        void* allocRef;
        if (g_isDebugFlag == 0) { // DAT_012056c8
            allocRef = nullptr;
            allocSize = 0;
        } else {
            allocRef = &g_isDebugFlag;
            allocSize = 4;
        }
        // Allocate resource from internal array at offset +0x1c (array of int handles)
        int newHandle = allocateResource(this->m_resourceHandles[resourceIndex], // +0x1c
                                          g_someGlobalData, // DAT_00e2e230
                                          allocSize,
                                          0,
                                          allocRef);
        this->m_resourceHandle = newHandle; // +0x34
        if (newHandle != 0) {
            // Initialize the context (likely a resource or stream object)
            constructObject(pContext); // FUN_004d3d90

            // Initialize local struct with global default
            SomeStruct initialData;
            initialData.field0 = g_globalDefaultValue; // DAT_01222258
            initialData.field1 = 0; // local_10
            initialData.field2 = 0; // local_c
            memset(&initialData, 0, sizeof(initialData)); // FUN_00408a00

            // Retrieve raw pointer from handle
            void* pResource = getResourcePointer(newHandle); // FUN_004025a0
            if (pResource != nullptr) {
                // Set a flag or state at offset +0x56 (e.g., stream state to 6 = active)
                setStreamStateOrFlag(pResource + 0x56, 6); // FUN_00402920
            }
        }
    }
}