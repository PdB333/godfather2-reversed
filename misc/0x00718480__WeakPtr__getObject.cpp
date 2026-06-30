// FUNC_NAME: WeakPtr::getObject
int * __fastcall WeakPtr::getObject(void *this) {
    int *objectPtr;

    // Check if internal handle pointer (offset +0x330) is valid
    int *handle = *(int **)((char *)this + 0x330);
    if (handle != nullptr) {
        objectPtr = (int *)((char *)handle - 0x48); // Adjust to get actual object (offset -0x48)
        if (objectPtr != nullptr) {
            return objectPtr;
        }
    }

    // Fallback to global manager for handle resolution
    int *globalManager = (int *)FUN_00722220();
    if (globalManager == nullptr) {
        return nullptr;
    }

    if (*globalManager == 0) {
        return nullptr;
    }

    return (int *)((char *)*globalManager - 0x48);
}