// FUNC_NAME: GodfatherGameManager::update
void __fastcall GodfatherGameManager::update(int this)
{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar2 = DAT_01223484;
  if ((DAT_01130044 != (int *)0x0) && ((char)DAT_01130044[0x12] != '\0')) {
    (**(code **)(*DAT_01130044 + 0x2c))();
  }
  if ((DAT_011307e8 != (int *)0x0) && ((char)DAT_011307e8[0x12] != '\0')) {
    (**(code **)(*DAT_011307e8 + 0x2c))();
  }
  if (*(int *)(this + 0xdc) == 0xb) {
    FUN_0096d810(0);
  }
  if (*(int *)(this + 0xdc) == 3) {
    iVar1 = this + 0x10;
    *(undefined4 *)(this + 0xc4) = 0;
    *(undefined4 *)(this + 0xd4) = 0;
    *(undefined4 *)(this + 0xd8) = 10;
    FUN_005c02f0(iVar1,&LAB_00969090,1);
    FUN_005c02f0(iVar1,&LAB_0096fba0,1);
    FUN_005c02f0(iVar1,&LAB_0096ccb0,1);
    FUN_005c02f0(iVar1,&LAB_0096ee00,1);
    *(undefined4 *)(this + 0xdc) = 5;
    FUN_00965720();
  }
  iVar1 = *(int *)(this + 0xdc);
  if (((iVar1 == 5) || (iVar1 == 7)) || (iVar1 == 8)) {
    FUN_0096ef50();
  }
  piVar4 = (int *)(iVar2 + 0x28);
  if (((*(int *)(iVar2 + 0x28) == 0 && *(int *)(iVar2 + 0x2c) == 0) || (piVar4 == (int *)0x0)) ||
     (DAT_011308b5 != '\0')) {
    DAT_011308b5 = '\0';
  }
  else {
    piVar3 = (int *)FUN_00ad8d40();
    if (piVar3 != (int *)0x0) {
      piVar3 = (int *)(**(code **)(*piVar3 + 0x30))();
      if (piVar3 != (int *)0x0) {
        DAT_011308b5 = 1;
        if (*piVar4 == 0 && *(int *)(iVar2 + 0x2c) == 0) {
          piVar4 = (int *)0x0;
        }
        (**(code **)(*piVar3 + 0x30))(*piVar4,piVar4[1]);
        return;
      }
      *piVar4 = 0;
      *(undefined4 *)(iVar2 + 0x2c) = 0;
      return;
    }
  }
  return;
}