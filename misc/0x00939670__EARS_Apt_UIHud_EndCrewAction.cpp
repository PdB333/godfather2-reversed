// Xbox PDB: EARS_Apt_UIHud_EndCrewAction
// FUNC_NAME: PlayerActionableInfo::endCrewAction
void __thiscall PlayerActionableInfo::endCrewAction(PlayerActionableInfo *this, undefined4 param_2, undefined4 result)
{
  int iVar1;
  
  if (*(char *)((int)this + 0x48) != '\0') {
    iVar1 = FUN_007351c0(); // likely getCurrentGangsterOrPlayer
    if (iVar1 != 0) {
      iVar1 = FUN_007351c0(); // getCurrentAgain (returns something)
      *(undefined4 *)((int)this + 0x70) = *(undefined4 *)(iVar1 + 0xc4); // copy some field from that object
    }
    *(undefined4 *)((int)this + 0x7c) = result; // store result at +0x7C
    FUN_005a04a0("EndCrewAction",0,&DAT_00d8a64c,0); // trigger event/send message
  }
  return;
}