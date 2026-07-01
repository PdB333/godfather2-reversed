// Xbox PDB: EARS_Modules_GamePlayLogging_PlayerSnapShot
// FUNC_NAME: DebugManager::logPlayerWeaponAndHealth
void __fastcall DebugManager::logPlayerWeaponAndHealth(int this)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  float10 fVar7;

  // Check if debug logging is enabled and the player object is valid
  if ((((DAT_012233a0 != 0) && (*(char *)(this + 0x10) != '\0')) &&
      (iVar6 = **(int **)(DAT_012233a0 + 4), iVar6 != 0)) &&
     ((piVar1 = (int *)(iVar6 + -0x1f30), piVar1 != (int *)0x0 && (*(int *)(iVar6 + 0x578) != 0))))
  {
    // Log weapon info for up to 5 weapons
    FUN_008d1330(); // likely a log header function
    iVar6 = 0;
    do {
      iVar2 = FUN_00705ab0(); // get weapon at index iVar6
      uVar5 = 0;
      uVar3 = 0;
      pcVar4 = "gun ?";
      if (iVar2 != 0) {
        uVar5 = *(undefined4 *)(iVar2 + 0x510); // weapon level? +0x510
        uVar3 = FUN_007013c0(); // get weapon ammo? +0x??
        pcVar4 = *(char **)(iVar2 + 0x1b8); // weapon name string +0x1B8
        if (pcVar4 == (char *)0x0) {
          pcVar4 = &DAT_0120546e; // default "unknown" string
        }
      }
      FUN_008d1330(this, "---Weapon,%s,Level:%u,%u\n", pcVar4, uVar5, uVar3);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 5);
    // Log other player stats
    FUN_00704a00(); // get some stat
    FUN_008d1330(); // log it
    FUN_00704a10(); // get another stat
    FUN_008d1330(); // log it
    FUN_00704990(); // get another stat
    FUN_008d1330(); // log it
    // Log player health
    fVar7 = (float10)(**(code **)(*piVar1 + 0xc4))(); // get max health
    fVar7 = (float10)(**(code **)(*piVar1 + 0xc0))((double)fVar7); // get current health percentage
    FUN_008d1330(this, "---Player Health,%f,%f\n", (double)fVar7);
  }
  return;
}