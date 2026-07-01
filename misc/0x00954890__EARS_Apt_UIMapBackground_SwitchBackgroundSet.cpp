// Xbox PDB: EARS_Apt_UIMapBackground_SwitchBackgroundSet
// FUNC_NAME: DebugMenu::registerSwitchSet
void DebugMenu::registerSwitchSet(undefined4 param_1)
{
    // +0x0: Register a switch set with the debug menu system
    // FUN_005a04a0 is likely DebugMenu::addItem or similar registration function
    // DAT_00d8c018 is likely a pointer to a debug menu manager instance
    FUN_005a04a0("SwitchSet", 0, &DAT_00d8c018, 1, param_1);
    return;
}