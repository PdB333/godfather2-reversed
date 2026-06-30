// FUNC_NAME: AudioDataManager::createInstance
void __cdecl AudioDataManager::createInstance(AudioDataManager* pManager, int handleId)
{
    // Allocate memory for a new AudioDataManager instance (size 0x14 = 20 bytes, 5 uint32 fields)
    AudioDataManager* pNewManager = (AudioDataManager*) allocMemory(0x14);
    if (pNewManager != nullptr) {
        // Initialize fields: offset 0x00 = this (parent object pointer), offset 0x10 = handleId
        pNewManager->parent = pManager;          // +0x00
        pNewManager->handleId = handleId;        // +0x10

        // Prepare request structure: type=2, size=0x10, flags=0
        int requestData[3] = { 2, 0x10, 0 };

        // Call virtual function at vtable index 0 of the parent object (likely a "create" method)
        // Passes handleId and pointer to requestData
        int result = pManager->vtable[0](handleId, requestData);  // vfunc returns some handle or pointer

        // Duplicate result into two fields offset 0x08 and 0x0C
        pNewManager->resourceA = result;          // +0x08
        pNewManager->resourceB = result;          // +0x0C

        // Initialize field offset 0x04 to 0 (maybe a ref count)
        pNewManager->counter = 0;                 // +0x04

        // Store the new instance in the global singleton pointer
        g_audioDataManager = pNewManager;
        return;
    }
    // Allocation failed; clear the global
    g_audioDataManager = nullptr;
}