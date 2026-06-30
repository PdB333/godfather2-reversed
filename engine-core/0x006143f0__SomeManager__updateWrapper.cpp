// FUNC_NAME: SomeManager::updateWrapper
void __thiscall SomeManager::updateWrapper(SomeManager* this, int param2, int param3, int param4, int param5) {
    // Calls the core update function with additional global pointers.
    // gGlobalData1 and gGlobalData2 are likely engine-level globals.
    FUN_00614440(param2, param3, param4, param5, &gGlobalData1, &gGlobalData2, this);

    // If the debug flag (low bit of gDebugFlags) is set, perform debug-specific update.
    if ((gDebugFlags & 1) != 0) {
        FUN_00614b90();
    }
}