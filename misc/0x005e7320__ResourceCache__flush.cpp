// FUNC_NAME: ResourceCache::flush
// Reconstructed from Ghidra at 0x005e7320
// Releases up to 4 cached resources via a manager object, then flushes the manager.

void ResourceCache::flush() {
    // this + 0x14: pointer to a manager object (e.g., ResourceManager)
    if (this->manager != nullptr) {
        // this + 0x4: array of 4 resource pointers (0x4, 0x8, 0xC, 0x10)
        for (int i = 0; i < 4; i++) {
            if (this->slots[i] != nullptr) {
                // vtable+4: release(resource, flag) – virtual function of manager
                this->manager->release(this->slots[i], 0);
                this->slots[i] = nullptr;
            }
        }
        // vtable+12: flushAll() – virtual function of manager
        this->manager->flushAll();
        this->manager = nullptr;
    }
}