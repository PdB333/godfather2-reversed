// FUN_NAME: SimManager::isManagedObject
bool __thiscall SimManager::isManagedObject(void* object) {
    if (object == 0) {
        return false;
    }
    // Pool base stored at this+0x603c, each object is 0x74 bytes
    int index = ((int)object - *(int*)((int)this + 0x603c)) / 0x74;
    // isValidPoolIndex checks if this index is valid (param2 = 1 indicates a specific check)
    return isValidPoolIndex(index, 1);
}