// FUNC_NAME: ObjectManager::getExtendedHandle
int ObjectManager::getExtendedHandle(int handle) {
    int basePtr = resolveObjectHandle(handle);
    if (basePtr != 0) {
        return basePtr + 9; // return pointer to offset 0x9 in object data (likely a variant or slot index)
    }
    return 0;
}