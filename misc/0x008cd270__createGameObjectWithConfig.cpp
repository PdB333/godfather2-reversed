// FUNC_NAME: createGameObjectWithConfig
int __cdecl createGameObjectWithConfig(int param1, int param2) {
    int gameManager = getGameManager(); // FUN_004a37d0 - likely returns singleton pointer
    // Check game manager validity: field +0x1c must be non-null, field +8 must be magic 0x1961bed, and subfield at +0x14 must be non-null
    if (*(int *)(gameManager + 0x1c) == 0 || 
        *(int *)(gameManager + 8) != 0x1961bed || 
        *(int *)(*(int *)(gameManager + 0x1c) + 0x14) == 0) {
        return 0;
    }

    uint *configPtr = (uint *)getConfigPointer(DAT_0112f98c); // FUN_004a3790 - likely returns config struct
    uint objectType = 1;
    if (configPtr != nullptr) {
        if ((*configPtr & 4) != 0) {
            objectType = 6;
        }
    }

    int obj = allocateMemory(0x20); // FUN_009c8e50 - custom allocation for 32 bytes
    if (obj != 0) {
        return constructGameObject(param1, param2, objectType); // FUN_008cd120 - actual constructor
    }
    return 0;
}