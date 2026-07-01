// FUNC_NAME: GameStateManager::resetDefaults
void __fastcall GameStateManager::resetDefaults(int thisPtr)
{
    char flag = *(char *)(thisPtr + 0x48); // Flag indicating if update logging is required
    int *dest = (int *)(thisPtr + 0x50); // +0x50: start of state data block (19 ints total)
    const int *src = gDefaultStateData; // DAT_00e54db8: default state values
    for (int i = 0x13; i != 0; --i)
    {
        *dest++ = *src++;
    }
    if (flag != '\0')
    {
        // Log an update event with "Update" string
        DebugPrint("Update", 0, &DAT_00d86e98, 0); // FUN_005a04a0
    }
    // Prepare a local struct for state initialization
    AlignmentStruct local;
    local.field0 = gSomeGlobal; // DAT_011301d8
    local.field4 = 0;
    local.field8 = 0;
    StateInitFunction(&local, 0); // FUN_00408a00: likely sets internal timers or flags
}