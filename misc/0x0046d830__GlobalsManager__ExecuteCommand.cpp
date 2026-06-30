// FUNC_NAME: GlobalsManager::ExecuteCommand
void GlobalsManager::ExecuteCommand(void)
{
    // Get the global manager singleton (likely a singleton or static instance)
    // FUN_009c8f80 returns a pointer to the global manager object
    GlobalsManager* managerObj = (GlobalsManager*)FUN_009c8f80();

    // Command parameters: {mode, param1, param2}
    // 0x70 (112) is a command ID (e.g., kCmdSetVideoMode, kCmdSetSoundConfig)
    CommandParameters params;
    params.mode = 2;          // +0x00: mode or sub-command (e.g., windowed/fullscreen)
    params.param1 = 0x10;     // +0x04: first parameter (e.g., width = 16? or something else)
    params.param2 = 0;        // +0x08: second parameter (e.g., height = 0? or profile index)

    // Call method on manager via function pointer table (first member of manager is a vtable pointer?)
    // The call: (managerObj->vtable[0x70 / 4])(&params) or similar.
    // We use a direct function call through the vtable (since the compiler uses `(**(code **)*puVar1)(0x70, &local_c)`)
    managerObj->VTableExecute(0x70, &params);
}