// Xbox PDB: EARS_Apt_UIHud_UpdateCrewActionTimer
// FUNC_NAME: CrewLeaderComponent::updateCrewActionTimer
void __thiscall CrewLeaderComponent::updateCrewActionTimer(int this, float param_2, float param_3, float param_4)
{
  int iVar1;
  float fVar2;
  
  if (*(char *)(this + 0x48) != '\0') { // +0x48: m_bCrewActionActive
    iVar1 = FUN_007351c0(); // likely getPlayer() or getLocalPlayer()
    if (iVar1 != 0) {
      iVar1 = FUN_007351c0(); // likely getPlayer() again
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar1 + 0xc4); // +0x70: m_crewActionTimer, +0xc4: player's some timer value
    }
    fVar2 = (param_3 / param_4) * DAT_00d5f4b4; // DAT_00d5f4b4 is likely a global max timer constant
    if (0.0 < fVar2) {
      if (DAT_00d5f4b4 <= fVar2) {
        fVar2 = DAT_00d5f4b4;
      }
    }
    else {
      fVar2 = 0.0;
    }
    *(float *)(this + 0x74) = fVar2; // +0x74: m_crewActionTimerClamped
    FUN_005a04a0("UpdateCrewActionTimer",0,&DAT_00d8a64c,0); // debug logging
  }
  return;
}