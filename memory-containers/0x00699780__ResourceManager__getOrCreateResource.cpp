// FUNC_NAME: ResourceManager::getOrCreateResource
// Function at 0x00699780: Attempts to find or create a resource entry.
// param_1 (this): pointer to ResourceManager instance
// param_2: resource key (hash or ID)
// param_3: additional creation data
// Returns 0 on failure (no action) or result of creation log.

undefined1 __thiscall ResourceManager::getOrCreateResource(int thisObj, undefined4 resourceKey, undefined4 creationData)
{
    undefined1 result;
    int *resourceEntry;

    result = 0;
    // Look up resource entry by key; returns pointer to entry structure
    resourceEntry = (int *)lookupResource(&resourceKey, resourceKey);
    // Check if the entry's ID matches this manager's slot ID (this+4)
    if (*resourceEntry != thisObj + 4) {
        // If mismatch, initialize the resource at offset 0x20 of the entry
        initializeResource(*resourceEntry + 0x20);
        // Log creation with global format string and creation data
        result = logResourceCreation(&DAT_0120546e, creationData);
    }
    return result;
}