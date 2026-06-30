// FUN_004b2590: AssetManager::loadSpecificResource
void AssetManager::loadSpecificResource(void)
{
    // The resource config struct (3 dwords)
    struct ResourceConfig {
        uint32_t type;   // +0x00 = 2
        uint32_t size;   // +0x04 = 0x10
        uint32_t flags;  // +0x08 = 0
    } config;

    config.type = 2;
    config.size = 0x10;
    config.flags = 0;

    // Get the singleton AssetManager instance
    void** assetMgr = (void**)GetAssetManager();

    // Call the first virtual method (likely loadResource) with resource ID 0x908 and config pointer
    ((void (*)(int, ResourceConfig*))(*assetMgr[0]))(0x908, &config);
}