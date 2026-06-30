// FUNC_NAME: ResourceCache::getEntry
// Address: 0x005de7e0
// Role: Retrieves a cached resource by key, checking validity first.
// Returns true if entry exists and writes it to output, false otherwise.

bool __thiscall ResourceCache::getEntry(ResourceKey key, ResourceEntry* outEntry) {
    // Check if cache is initialized/valid
    if (this->isReady()) {  // FUN_005dc670 - likely checks internal state
        *outEntry = this->fetchData(key);  // FUN_005dd910 - retrieves data by key
        return true;
    }
    return false;
}