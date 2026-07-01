// Xbox PDB: EARS_Modules_NPCActionSM_BuildActionTransitions
// FUNC_NAME: NPCManager::registerNPCActions
void NPCManager::registerNPCActions(void)
{
    // Register NPC action types with their string names and IDs
    // FUN_004acd20 is likely ActionManager::registerAction or similar
    // Parameters: actionName, actionType, actionID, unknownFlag
    FUN_004acd20(&DAT_00d69544, 0x12, 0x1c, 1);  // Guard action
    FUN_004acd20("Guard", 0x12, 0x1d, 1);         // Guard (duplicate?)
    FUN_004acd20(&DAT_00d69534, 0x12, 0x20, 1);   // Unknown string
    FUN_004acd20("DrawGunAction", 0x12, 1, 1);
    FUN_004acd20("HolsterGunAction", 0x12, 2, 1);
    FUN_004acd20("ReloadGunAction", 0x12, 3, 1);
    FUN_004acd20("FireGunStationaryAction", 0x12, 4, 1);
    FUN_004acd20("StrafeFire", 0x12, 5, 1);
    FUN_004acd20("RangedChase", 0x12, 6, 1);
    FUN_004acd20("EnterCover", 0x12, 7, 1);
    FUN_004acd20("ExitCover", 0x12, 8, 1);
    FUN_004acd20("CoverPeek", 0x12, 9, 1);
    FUN_004acd20("CoverPeekFire", 0x12, 10, 1);
    FUN_004acd20("CoverBlindFire", 0x12, 0xb, 1);
    FUN_004acd20("ChangeCoverNode", 0x12, 0xc, 1);
    FUN_004acd20("ActThreatening", 0x12, 0xd, 1);
    FUN_004acd20("Cower", 0x12, 0xe, 1);
    FUN_004acd20("Startle", 0x12, 0xf, 1);
    FUN_004acd20("Follow", 0x12, 0x10, 1);
    FUN_004acd20("Surrender", 0x12, 0x13, 1);
    FUN_004acd20("Search", 0x12, 0x14, 1);
    FUN_004acd20("RandomSearch", 0x12, 0x15, 1);
    FUN_004acd20("EquipMeleeWeapon", 0x12, 0x16, 1);
    FUN_004acd20("ConcealMeleeWeapon", 0x12, 0x17, 1);
    FUN_004acd20("MeleeAttack", 0x12, 0x18, 1);
    FUN_004acd20("Evade", 0x12, 0x19, 1);
    FUN_004acd20("MeleeChase", 0x12, 0x1a, 1);
    FUN_004acd20("MeleeSpectate", 0x12, 0x1b, 1);
    FUN_004acd20("ApproachCrimeScene", 0x12, 0x22, 1);
    FUN_004acd20("Inform", 0x12, 0x21, 1);
    FUN_004acd20("WitnessIdle", 0x12, 0x23, 1);
    FUN_004acd20("CrimeSceneSearch", 0x12, 0x24, 1);
    FUN_004acd20("UseInterestingObject", 0x12, 0x25, 1);
    FUN_004acd20("Backup", 0x12, 0x26, 1);
    FUN_004acd20(&DAT_00d6937c, 0x12, 0x27, 1);  // Unknown string
    FUN_004acd20("CrewCommand", 0x12, 0x2a, 1);
    FUN_004acd20("CombatFlee", 0x12, 0x28, 1);
    FUN_004acd20("InteriorFlee", 0x12, 0x29, 1);
    FUN_004acd20("DesignerAction", 0x12, 0x2c, 1);
    FUN_004acd20("PickupWeapon", 0x12, 0x2b, 1);
    FUN_004acd20("ApproachTakeoverVenue", 0x12, 0x2d, 1);
    FUN_004acd20("WitnessIntimidation", 0x12, 0x2e, 1);
    FUN_004acd20("StopWitnessing", 0x12, 0x2f, 1);
    FUN_004acd20("OwnerIntimidation", 0x12, 0x30, 1);
    FUN_004acd20("BuildingSearch", 0x12, 0x31, 1);
    FUN_004acd20("BackupFromTarget", 0x12, 0x32, 1);
    FUN_004acd20("BreakGuard", 0x12, 0x1e, 1);
    FUN_004acd20("ReformGuard", 0x12, 0x1f, 1);
    FUN_004acd20("FindPedGraph", 0x12, 0x33, 1);
    FUN_004acd20("ScaredBackup", 0x12, 0x34, 1);
    return;
}