// FUNC_NAME: SimManager::getResourceDataByTypeID

unsigned int __thiscall SimManager::getResourceDataByTypeID(int this)
{
    // +0x78: count of resource type IDs in list
    int resourceCount = *(int *)(this + 0x78);
    if (resourceCount > 0)
    {
        // +0x74: pointer to array of 32-bit resource type IDs
        int *resourceTypeList = *(int **)(this + 0x74);
        for (int idx = 0; idx < resourceCount; idx++)
        {
            // 0x34133103 is a specific resource type identifier (e.g., object type or hash)
            if (resourceTypeList[idx] == 0x34133103)
            {
                char keyBuffer[12]; // likely a temporary resource key structure (12 bytes)
                unsigned int *result = (unsigned int *)createResourceKey(keyBuffer, 0x34133103);
                return *result; // return the first DWORD of the resource key data
            }
        }
    }
    // Default fallback resource type ID (0x801) if target not found
    char keyBuffer[12];
    unsigned int *result = (unsigned int *)createResourceKey(keyBuffer, 0x801);
    return *result;
}