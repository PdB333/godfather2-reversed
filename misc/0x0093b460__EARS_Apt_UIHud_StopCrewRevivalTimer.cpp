// Xbox PDB: EARS_Apt_UIHud_StopCrewRevivalTimer
// FUNC_NAME: NPCCrewComponent::stopCrewRevivalTimer
void __thiscall NPCCrewComponent::stopCrewRevivalTimer(int this, undefined4 param_2, char param_3)
{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Check if revival timer is active (flag at +0x48)
  if (*(char *)(this + 0x48) != '\0') {
    iVar1 = FUN_007351c0(); // Get some global object (likely GameManager or SimManager)
    if (iVar1 != 0) {
      iVar1 = FUN_007351c0(); // Get another object from it
      // Copy some value from that object's +0xC4 into this->+0x70
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar1 + 0xc4);
    }
    // Log "StopCrewRevivalTimer" with some debug/tracking function
    FUN_005a04a0("StopCrewRevivalTimer",0,&DAT_00d8a64c,0);
  }
  
  // Get some value (likely a crew member index or ID)
  param_2 = FUN_0043b490();
  iVar1 = FUN_0093b3f0(&param_2); // Find crew member index from ID
  if (-1 < iVar1) {
    // Clear the crew member at this index (offset +0x174 is crew array, each entry 8 bytes)
    FUN_0094b0e0(*(undefined4 *)(*(int *)(this + 0x174) + 4 + iVar1 * 8));
    // Remove crew member from list
    FUN_0093a120(iVar1);
  }
  
  local_8 = 0;
  local_4 = 0;
  if (param_3 != '\0') {
    // If param_3 is true, use DAT_01130328 (likely a different sound/effect)
    local_c = DAT_01130328;
    FUN_00408a00(&local_c,0); // Play sound or trigger effect
    return;
  }
  // Default sound/effect
  local_c = DAT_01130260;
  FUN_00408a00(&local_c,0);
  return;
}