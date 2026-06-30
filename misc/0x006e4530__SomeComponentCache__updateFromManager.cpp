// FUNC_NAME: SomeComponentCache::updateFromManager
void SomeComponentCache::updateFromManager() {
    // this+0x100 points to a manager object (e.g., SingletonManager or ComponentManager)
    ComponentManager* mgr = *(ComponentManager**)((int)this + 0x100);
    void* component = nullptr;

    // First attempt: try to retrieve component with hash 0x383225a1
    bool found = mgr->vtableFnAt0x10(0x383225a1);  // returns bool, maybe just existence check
    if (!found || component == nullptr) {
        component = nullptr;
        // Second attempt: query with hash 0x55859efa, storing the result in component
        found = mgr->vtableFnAt0x10(0x55859efa, &component);
        if (!found ||
            component == nullptr ||
            *(int*)((int)component + 0xffc) == 0 ||
            (component = (void*)(*(int*)((int)component + 0xffc) - 0x48), component == nullptr)) {
            // On failure, store a self-pointer as sentinel (or this pattern indicates null)
            // In original, this seems to be a fallback that writes the object's address to itself
            // Likely a mistake in decompilation; we treat it as a null assignment
            *(int**)this = (int*)this; // store self pointer as error marker
            return;
        }
    }
    // Success: read a pointer from the component at offset 0x2894 and store at this+0
    *(int**)this = *(int**)((int)component + 0x2894);
}