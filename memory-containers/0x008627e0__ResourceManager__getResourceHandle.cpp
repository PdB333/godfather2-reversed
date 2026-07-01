// FUNC_NAME: ResourceManager::getResourceHandle
// Function address: 0x008627e0
// Role: Retrieves a resource handle from a container structure.
// The container has fields at offset 0 (valid flag) and offset 8 (resource data).
// Returns 0 if invalid, otherwise returns the resource data with its low byte replaced by 1.

uint32_t __thiscall ResourceManager::getResourceHandle(int* thisPtr, int* outValid, int* outData)
{
    int validFlag = *thisPtr;               // +0x00: valid flag
    *outValid = validFlag;
    if (validFlag != 0) {
        int resourceData = thisPtr[2];      // +0x08: resource data (e.g., ID or pointer)
        *outData = resourceData;
        // Combine: keep upper 24 bits of resourceData, set low byte to 1
        return (resourceData & 0xFFFFFF00) | 0x01;
    }
    *outData = 0;
    return 0;
}