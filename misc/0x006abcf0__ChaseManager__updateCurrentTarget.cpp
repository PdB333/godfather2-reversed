// FUNC_NAME: ChaseManager::updateCurrentTarget
int __thiscall ChaseManager::updateCurrentTarget(ChaseManager *this) {
    // +0x10: pointer to current target object
    int *targetPtr = *(int **)((char *)this + 0x10);
    if (targetPtr == nullptr) {
        return 0;
    }

    // +0x78: state field in target object (2 bytes)
    short state = *(short *)((char *)targetPtr + 0x78);

    if (state == 0) {
        // State 0 means target is invalid – clear the pointer
        *(int **)((char *)this + 0x10) = nullptr;
    } else if (state == 1 && targetPtr == *(int **)((char *)this + 0x14)) {
        // State 1 and target matches the previous target (+0x14) – clear previous target
        *(int **)((char *)this + 0x14) = nullptr;
    }

    if (targetPtr != nullptr) {
        // +0x24: base float; +0x2c: updated float (e.g., timer or position)
        // DAT_01205228 is a global constant (e.g., delta time or speed factor)
        *(float *)((char *)this + 0x2c) = *(float *)((char *)this + 0x24) + DAT_01205228;
        return (int)targetPtr;
    }
    return 0;
}