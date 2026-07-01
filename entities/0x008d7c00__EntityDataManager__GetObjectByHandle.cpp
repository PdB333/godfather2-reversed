// FUNC_NAME: EntityDataManager::GetObjectByHandle
int __thiscall EntityDataManager::GetObjectByHandle(int this, int handle) {
    int indexResult;
    int elementPtr;

    // First try: direct index lookup using handle as key?
    indexResult = FUN_008d72e0(&handle);  // FindIndexByHandle?
    if (indexResult >= 0) {
        elementPtr = *(int *)(this + 0x38) + 4 + indexResult * 0x18; // +0x38: pointer to array of handles/objects? Each entry 0x18 bytes, +4 offset?
        if (elementPtr != 0) {
            return elementPtr + 0xc; // +0xc: actual object data within entry?
        }
    }

    // Fallback: slower lookup
    indexResult = FUN_008d77e0(&handle);  // FindByFallbackTable?
    FUN_008d5e80(); // EnsureFallbackTableInitialized?
    return indexResult + 0xc; // Again offset by 0xc
}