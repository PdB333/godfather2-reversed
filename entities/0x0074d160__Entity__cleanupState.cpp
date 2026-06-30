// FUNC_NAME: Entity::cleanupState
bool __thiscall Entity::validateAndRelease(int this, int param) {
    char valid = FUN_0074ce90(param); // bool isValidOrCanRelease(param)
    if (valid == '\0') {
        FUN_0074cfe0(); // scheduleDeferredCleanup()
        return false;
    }
    int* resourcePtr = (int*)(this + 0x94); // +0x94: pointer to sub-resource
    if (*(int*)(this + 0x94) != 0) {
        FUN_006e6430(0, *(undefined4*)(this + 0x88)); // stopSound(0, soundId at +0x88)
        if (*resourcePtr != 0) {
            FUN_004daf90(resourcePtr); // freeSubResource(resourcePtr)
            *resourcePtr = 0;
        }
    }
    return true;
}