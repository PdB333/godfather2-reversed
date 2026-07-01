// Xbox PDB: EARS_Apt_UIOnlineMenu_SetCurrentStatus
// FUNC_NAME: PlayerSM::setState
void __thiscall PlayerSM::setState(int this, int newState)
{
  int oldState;
  undefined4 uVar2;
  
  oldState = *(int *)(this + 0xdc);
  if (oldState == newState) {
    return;
  }
  *(undefined4 *)(this + 0xc4) = 0;
  *(undefined4 *)(this + 0xd4) = 0;
  switch(oldState) {
  case 1:
  case 6:
    uVar2 = 9;
    break;
  default:
    uVar2 = 10;
  }
  *(undefined4 *)(this + 0xd8) = uVar2;
  if (oldState == 4) {
    FUN_005a04a0("HideReadyState",0,&DAT_00d8cdec,0);
  }
  if (*(int *)(this + 0xdc) == 1) {
    FUN_0096adc0();
  }
  if (newState == 0) {
    *(undefined1 *)(this + 500) = 0;
    *(undefined1 *)(DAT_01129914 + 0xd3) = 0;
    FUN_0095eb90(0);
    *(undefined1 *)(this + 500) = 0;
LAB_0097049e:
    FUN_005c02f0(this + 0x10,&LAB_00969090,1);
    if (newState != 0) goto LAB_009704ce;
    *(undefined1 *)(this + 0x220) = 0;
    FUN_005a04a0("ClearHistory",0,&DAT_00d8cdec,0);
  }
  else {
    if (newState != 1) goto LAB_0097049e;
LAB_009704ce:
    if ((newState == 5) || (newState == 3)) goto LAB_009704e8;
  }
  FUN_005c02f0(this + 0x10,&LAB_00963ee0,1);
LAB_009704e8:
  if (newState != 6) {
    FUN_005c02f0(this + 0x10,&LAB_0096fba0,1);
  }
  if (newState != 7) {
    FUN_005c02f0(this + 0x10,&LAB_0096ccb0,1);
  }
  if (newState != 4) {
    FUN_005c02f0(this + 0x10,&LAB_0096ee00,1);
  }
  *(int *)(this + 0xdc) = newState;
  FUN_00965720();
  return;
}