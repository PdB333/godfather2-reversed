// FUNC_NAME: ResourceManager::acquireGameResource
void ResourceManager::acquireGameResource() {
    // Determine resource type based on global flag 'g_bUseCustomResource'
    int resourceType = 3;
    if (g_bUseCustomResource != '\0') {
        resourceType = 3 + 0x11; // 0x14?
    }
    // Actually the expression is: (-(g_bUseCustomResource != '\0') & 0x11U) + 3
    // This yields either 3 (if false) or 3+0x11=0x14 (if true)
    int adjustedType = ((-(g_bUseCustomResource != 0)) & 0x11) + 3;
    
    // Call the resource acquisition function (likely memory allocation or file load)
    // Arguments: type, resourceID 0x210098, param1, param2, flags=1, unknown=-1
    void* resourceHandle = acquireResourceCore(adjustedType, 
                                               0x210098,          // resource ID (hash?)
                                               g_resourceParam1,
                                               g_resourceParam2,
                                               1,                // some flag
                                               -1);              // unknown
    
    // Store the handle at offset +0xA4 in this object (e.g., "m_pResourceHandle")
    *(void**)(this + 0xA4) = resourceHandle;
    
    // If the global game state is not 1 ("playing") nor 2 ("paused"), perform additional setup
    if (g_gameState != 1 && g_gameState != 2) {
        performSetupInterface(); // FUN_00618910
    }
}