// FUNC_NAME: ResourceManager::releaseActive
int ResourceManager::releaseActive(void) {
    int retVal = 0; // return value (0 = nothing released, 1 = released)

    // Check if the resource is active/loaded (byte at +0x490)
    if (this->m_isLoaded) {
        // Call internal cleanup method (FUN_005e8300)
        this->stop(); // likely stops/unloads the resource

        // Clear the active flag
        this->m_isLoaded = false;

        // If a resource pointer is valid, call its custom deleter function
        // m_pResource (+0x494) is the resource object
        // m_pDeleter (+0x4a0) is a function pointer for release/deletion
        if (this->m_pResource != nullptr) {
            (this->m_pDeleter)(this->m_pResource);
        }

        // Zero out resource pointer and auxiliary fields
        this->m_pResource = nullptr;       // +0x494
        this->m_field49c = 0;              // +0x49c (unused count/flag)
        this->m_field498 = 0;              // +0x498 (unused count/flag)
        retVal = 1;                        // signal that cleanup occurred
    }

    return retVal;
}