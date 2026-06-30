// FUNC_NAME: ResourceLoader::updateResourceId
uint32_t __fastcall ResourceLoader::updateResourceId(void* this) {
    // +0xE4: uint32_t m_resourceId
    // +0xE8: uint32_t m_flags
    uint32_t resourceId = *(uint32_t*)((uint8_t*)this + 0xE4);
    uint32_t flags = *(uint32_t*)((uint8_t*)this + 0xE8);
    const uint32_t kFlagLoaded = 0x40;
    const uint32_t kFlagError = 0x80;
    const uint32_t kInvalidResourceId = 0xbfa3eec8;

    if ((flags & kFlagLoaded) == 0) {
        // Attempt to allocate memory/resource of size 0x80
        if (allocateMemory(0x80)) {
            // Attempt to load the resource
            if (loadResource()) {
                // Mark as loaded
                flags |= kFlagLoaded;
                *(uint32_t*)((uint8_t*)this + 0xE8) = flags;
            }
        }
        // Check for error flag
        if (flags & kFlagError) {
            return kInvalidResourceId;
        }
        return resourceId;
    } else {
        // Resource already loaded – check if still valid
        if (!checkResourceValidity()) {
            // Mark as not loaded
            flags &= ~kFlagLoaded;
            *(uint32_t*)((uint8_t*)this + 0xE8) = flags;
        }
        if (flags & kFlagError) {
            return kInvalidResourceId;
        }
        return resourceId;
    }
}