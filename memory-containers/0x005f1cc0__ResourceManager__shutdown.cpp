// FUNC_NAME: ResourceManager::shutdown
void ResourceManager::shutdown(void)
{
    // Check if the manager object exists, if it has a valid flag, and if a cleanup function pointer is set
    if ( (g_pResourceManager != 0) && ((g_resourceFlags & 1) != 0) && (*(int *)(g_pFunctionTable + 4) != 0) )
    {
        // Call the cleanup/release function through vtable at offset 4
        (**(code **)(**(int **)(g_pFunctionTable + 4) + 4))(g_pResourceManager, 0);
    }

    // Reset all manager state to zero
    g_pResourceManager          = 0;  // +0x00: object pointer
    g_resourceCounter           = 0;  // +0x04: counter
    g_resourceData1             = 0;  // +0x08: some data
    g_resourceData2             = 0;  // +0x0C: some data
    g_resourceData3             = 0;  // -0x04 relative: earlier field? actually at 0x011a0efc
    g_resourceFlags             = 0;  // +0x10: bitfield flag
    g_resourceData4             = 0;  // -0x10: earlier field? at 0x011a0ef0
    g_resourceData5             = 0;  // -0x0C: at 0x011a0ef4
    g_resourceByte              = 0;  // -0x06: at 0x011a0efa (byte?)
    g_resourceDefaultFlag       = 0x80; // -0x08: at 0x011a0ef8 (set to 0x80)
}