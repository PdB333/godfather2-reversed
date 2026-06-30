// FUNC_NAME: PlayerStateManager::getCurrentGameState
int __fastcall PlayerStateManager::getCurrentGameState(void* thisPtr) {
    // this+4 points into a sub-object; subtract 0x48 to get base of container structure
    char* containerBase = *(char**)((char*)thisPtr + 4);
    if (containerBase == nullptr) {
        return 0;
    }
    containerBase -= 0x48; // realign to start of container

    // container+0x200c holds a pointer to another sub-object, subtract 0x3c to get its base
    char* stateContainer = *(char**)(containerBase + 0x200c);
    if (stateContainer == nullptr) {
        return 0;
    }
    stateContainer -= 0x3c; // realign

    // Global singleton check; DAT_012233a0+4 holds a pointer to a controller/manager
    int* globalObj = *(int**)(DAT_012233a0 + 4);
    if (globalObj != nullptr && (int)globalObj != 0x1f30 && *(int*)((char*)globalObj + 0x578) != 0) {
        // stateContainer+0x50 holds the current game state
        int state = *(int*)(stateContainer + 0x50);
        switch (state) {
        case 6:
            return FUN_00704720(); // returns corresponding state value
        case 7:
            return FUN_00704730();
        case 8:
            return FUN_00704740();
        default:
            break;
        }
    }
    return 0;
}