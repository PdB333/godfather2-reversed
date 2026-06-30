// FUNC_NAME: VFXManager::createEffect
undefined4 __fastcall VFXManager::createEffect(undefined4 initData) {
    // Get the singleton VFX manager (0x009c8f80)
    undefined4* managerPtr = (undefined4*)VFXManager::getSingleton();
    // Allocation parameters: pool 2, alignment 0x10, flags 0
    struct AllocParams {
        int pool;       // +0x00: memory pool identifier
        int alignment;  // +0x04: memory alignment
        int flags;      // +0x08: allocation flags
    } allocInfo;
    allocInfo.pool = 2;
    allocInfo.alignment = 0x10;
    allocInfo.flags = 0;
    // Call virtual allocate function (vtable[0]) - size 0x80 bytes (128)
    int allocResult = (*(int (__fastcall**)(undefined4, void*))*managerPtr)(0x80, &allocInfo);
    if (allocResult != 0) {
        // Construct the VFX effect, returns the object pointer
        undefined4 result = FUN_006da310(initData);
        return result;
    }
    return 0;
}