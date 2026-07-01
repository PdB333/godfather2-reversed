// Xbox PDB: EARS_Apt_UIHud_HideNPCInfo
// FUNC_NAME: NPCInfoManager::hideNPCInfo

void __fastcall NPCInfoManager::hideNPCInfo(NPCInfoManager* thisPtr)
{
    // +0x114: pointer to a resource (possibly NPC info overlay object)
    if (thisPtr->field_0x114 != 0) {
        releaseObject(&thisPtr->field_0x114);  // FUN_004daf90
        thisPtr->field_0x114 = 0;
    }
    // +0x11c: another pointer to a resource
    if (thisPtr->field_0x11c != 0) {
        releaseObject(&thisPtr->field_0x11c);  // FUN_004daf90
        thisPtr->field_0x11c = 0;
    }
    // +0x104: clear some state/pointer
    thisPtr->field_0x104 = 0;
    // +0x5c: flags; clear bit 11 (0x800) - hide NPC info flag
    thisPtr->flags &= ~0x800;
    // Execute debug console command to hide NPC info, passing a global data pointer
    executeConsoleCommand("HideNPCInfo", 0, &DAT_00d8a64c, 0);  // FUN_005a04a0
}