// Xbox PDB: EARS_Apt_UIHud_UpdateCrewRevivalTimer
// FUNC_NAME: PlayerCrewLeaderComponent::updateCrewRevivalTimer
void __thiscall PlayerCrewLeaderComponent::updateCrewRevivalTimer(int this, undefined4 param_2, float param_3, float param_4)
{
  int iVar1;
  float fVar2;
  
  if (*(char *)(this + 0x48) != '\0') {
    iVar1 = FUN_007351c0(); // likely getGameManager() or getSimManager()
    if (iVar1 != 0) {
      iVar1 = FUN_007351c0(); // likely getPlayer() or getLocalPlayer()
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar1 + 0xc4); // copy some player state
    }
    fVar2 = (param_3 / param_4) * DAT_00d5f4b4; // DAT_00d5f4b4 is likely a max revival timer constant
    if (0.0 < fVar2) {
      if (DAT_00d5f4b4 <= fVar2) {
        fVar2 = DAT_00d5f4b4;
      }
    }
    else {
      fVar2 = 0.0;
    }
    *(float *)(this + 0x74) = fVar2; // store revival timer progress
    FUN_005a04a0("UpdateCrewRevivalTimer",0,&DAT_00d8a64c,0); // likely debug/log function
  }
  return;
}