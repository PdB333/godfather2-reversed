// FUNC_NAME: Container::releaseAndCleanup
struct Container {
    void*   child1;          // +0x00
    // unused padding        // +0x04, +0x08
    void*   child2;          // +0x0C
    void**  vtbl;            // +0x10
};

void __thiscall Container::releaseAndCleanup() {
    // Virtual function type: release(void* obj, int flag)
    typedef void (__thiscall *ReleaseFunc)(void*, int);
    // Virtual function type: final cleanup (no args)
    typedef void (__thiscall *CleanupFunc)();

    ReleaseFunc releaseChild = (ReleaseFunc)(this->vtbl[1]);  // vtable index 1 (offset +4)
    CleanupFunc cleanup = (CleanupFunc)(this->vtbl[3]);       // vtable index 3 (offset +0xC)

    // Release first child
    releaseChild(this->child1, 0);
    // Release second child if non-null
    if (this->child2 != 0) {
        releaseChild(this->child2, 0);
    }
    // Final cleanup
    cleanup();
}