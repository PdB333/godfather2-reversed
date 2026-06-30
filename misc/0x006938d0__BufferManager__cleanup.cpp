// FUNC_NAME: BufferManager::cleanup
void BufferManager::cleanup() {
    // Release the secondary buffer at offset +0x1c
    if (this->secondaryBuffer) {
        release(this->secondaryBuffer);
    }

    // Global cleanup (e.g., file handle, system resource)
    globalCleanup();

    // Release the primary buffer at offset +0x18
    release(this->primaryBuffer);

    // Sub-manager object at offset +0x04
    SubManager* sub = this->subManager;
    if (sub) {
        // Release internal buffer at sub +0x10
        release(sub->internalBuffer);
        // Release extra pointer at sub +0x04
        if (sub->extraData) {
            release(sub->extraData);
        }
        // Destroy the sub-manager itself
        destroySubManager(sub);
    }
}