// FUNC_NAME: GameManager::updateActiveFlag
void GameManager::updateActiveFlag(void) {
    // Global singleton pointer to GameManager instance at DAT_012233b8
    // Offset +0x94: pointer to some state object (e.g., active mission, menu)
    // Offset +0x10: flags field (bit 0 = active/enabled)

    if (*(int*)((unsigned char*)gGameManager + 0x94) != 0) {
        // Condition true: set active flag
        *(unsigned int*)((unsigned char*)gGameManager + 0x10) |= 1;
        return;
    }
    // Condition false: clear active flag
    *(unsigned int*)((unsigned char*)gGameManager + 0x10) &= 0xFFFFFFFE;

    // Unused locals (likely artifacts of decompilation)
    int dummy1 = 0;        // local_8
    char dummy2 = 0;       // local_4

    // Call reset/init function with global data and 0
    FUN_00408a00(&gSomeData, 0);  // gSomeData is the global at DAT_01206a20
}