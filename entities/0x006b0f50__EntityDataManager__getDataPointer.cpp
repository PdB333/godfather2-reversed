// FUNC_NAME: EntityDataManager::getDataPointer
undefined4 __thiscall EntityDataManager::getDataPointer(EntityDataManager *this, undefined4 handle) {
    int dataPtr;
    
    dataPtr = EntityDataManager::lookupHandle(this, handle);
    if (dataPtr != 0) {
        return *(undefined4 *)(dataPtr + 0x40); // +0x40: pointer to data block
    }
    return 0;
}