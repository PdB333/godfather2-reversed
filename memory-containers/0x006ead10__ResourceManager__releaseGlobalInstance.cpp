// FUNC_NAME: ResourceManager::releaseGlobalInstance
void ResourceManager::releaseGlobalInstance(void)
{
    int* pManager = g_pResourceManager; // DAT_0112a9c0
    if (pManager != 0) {
        // Check if the resource is not already released (byte at +0x78)
        if (*(char*)(pManager + 0x78) == '\0') {
            int* pResource = *(int**)(pManager + 0x60); // int at +0x60, likely a pointer to some resource
            if (pResource != 0) {
                // Build a temporary structure to pass to the release function
                // local_c[0] = resource pointer, local_c[1] = 0, local_4 = 0
                // This might be a RefCounted or SmartPtr-like struct
                int local_c[2];
                char local_4;
                local_c[0] = (int)pResource;
                local_c[1] = 0;
                local_4 = 0;
                // Call release function (FUN_00408a00) with the structure and a flag
                releaseResource(local_c, 0); // FUN_00408a00
                // Mark as released: set byte at +0x78 to 1
                *(char*)(pManager + 0x78) = 1;
            }
        }
        // Clear the global pointer
        g_pResourceManager = 0; // DAT_0112a9c0 = 0
    }
    return;
}