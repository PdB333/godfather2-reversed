// Xbox PDB: EARS_Apt_UIHud_StartCrewActionTimer
// FUNC_NAME: PlayerReputationTracker::updateCrewActionTimer
void __fastcall PlayerReputationTracker::updateCrewActionTimer(int this)
{
  int pObj;
  
  if (*(char *)(this + 0x48) != '\0') {
    pObj = FUN_007351c0();
    if (pObj != 0) {
      pObj = FUN_007351c0();
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(pObj + 0xc4);
    }
    FUN_005a04a0("StartCrewActionTimer",0,&DAT_00d8a64c,0);
  }
  return;
}