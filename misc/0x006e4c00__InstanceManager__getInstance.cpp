// FUNC_NAME: InstanceManager::getInstance
void InstanceManager::getInstance(void** outPointer) {
    // Access member at offset 0x100 (likely a pointer to a factory/manager object with vtable)
    void** managerPtr = (void**)((int)this + 0x100);
    // Magic constant identifying this instance type
    const uint32_t kClassHash = 0x369ac561;
    void* tempPointer = nullptr;

    // Virtual function at vtable+0x10 expects (hash, &tempPointer)
    // Returns true if instance exists, false if we need to create? 
    // In either case, tempPointer is set to a valid instance.
    bool exists = (*(bool (**)(void*, uint32_t, void**))(*(int*)*managerPtr + 0x10))(
        *managerPtr, kClassHash, &tempPointer);

    // The instance's first DWORD is set to the class hash as a signature/type identifier
    *(uint32_t*)tempPointer = kClassHash;
    *outPointer = tempPointer;
}