// FUNC_NAME: createGameObject
int createGameObject(int arg1, int arg2) {
    char isActive = isGameActive(); // FUN_00481620 - global game state check
    if (isActive) {
        int obj = allocateMemory(); // FUN_00471610 - allocate object (size unknown)
        int result = setFieldAtOffset30(obj + 0x30, arg2); // FUN_00811840 - set field at +0x30
        int someValue = getSomeValue(arg1, obj); // FUN_00811920 - retrieve resource/ID
        if (obj != 0) {
            int localVar = 0;
            char localBuffer[16]; // 16-byte buffer (e.g., GUID or transform)
            initLocalBuffer(localBuffer); // FUN_00811b90 - initialize buffer
            initSubObjects(obj + 0x60, someValue, obj + 0xa0, localBuffer); // FUN_0079e3c0 - init sub-objects at +0x60 and +0xa0
            return obj;
        } else {
            // Fallback path when allocation fails
            int fallbackObj = allocateMemory(someValue, 0, 0); // FUN_00471610 with three args
            initSubObjects(fallbackObj, someValue, 0, 0); // FUN_0079e3c0 - init with zeros
        }
    }
    return 0;
}