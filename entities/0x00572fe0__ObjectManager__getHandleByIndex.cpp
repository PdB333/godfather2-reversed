// FUNC_NAME: ObjectManager::getHandleByIndex
int __thiscall ObjectManager::getHandleByIndex(void) {
    int hashResult[4]; // local_8
    int index; // local_4

    index = FUN_00573db0(hashResult);
    if ((index != 0) && (*(int *)(index + 0x14) >= 0) && (*(int *)(index + 0x14) < *(int *)(this + 0x20))) {
        return *(int *)(this + 0x24) + *(int *)(index + 0x14) * 8;
    }
    return 0;
}