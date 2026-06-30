// FUNC_NAME: GodfatherGameManager::switchActiveFamily
void __thiscall GodfatherGameManager::switchActiveFamily(int thisPtr, int param2, int param3, undefined4 param4, char param5)
{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int in_EAX;
  uint uVar4;
  undefined4 *puVar5;
  
  if ((param1 != in_EAX) && (param2 != in_EAX)) {
    param3 = in_EAX;
  }
  uVar4 = 0;
  do {
    if ((&DAT_01218e50)[uVar4 * 2] == param3) {
      if (uVar4 < 0x14) {
        (&DAT_01218e54)[uVar4 * 2] = (&DAT_01218e54)[uVar4 * 2] & 0xfffffffc;
      }
      break;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x14);
  uVar2 = DAT_011f38f4;
  uVar1 = DAT_011f38f0;
  DAT_011f38f4 = 0;
  DAT_011f38f0 = param3;
  FUN_00609340(0,uVar1,uVar2);
  FUN_00609810(1);
  FUN_0053d470(0);
  FUN_0053d590();
  FUN_0053d310();
  puVar5 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
  uVar2 = DAT_00e2eff4;
  uVar1 = DAT_00e2b1a4;
  if (puVar5 != (undefined4 *)0x0) {
    *puVar5 = DAT_00e2eff4;
    puVar5[1] = uVar2;
    puVar5[2] = uVar1;
    puVar5[3] = uVar2;
    puVar5[4] = uVar1;
    puVar5[5] = uVar1;
    puVar5[6] = uVar2;
    puVar5[7] = uVar1;
    FUN_0060cde0();
  }
  FUN_00612e00();
  FUN_00609890(1);
  uVar4 = 0;
  do {
    if ((&DAT_01218e50)[uVar4 * 2] == param2) {
      if (uVar4 < 0x14) {
        (&DAT_01218e54)[uVar4 * 2] = (&DAT_01218e54)[uVar4 * 2] & 0xfffffffc;
      }
      break;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x14);
  uVar1 = DAT_011f38f4;
  iVar3 = DAT_011f38f0;
  DAT_011f38f0 = param2;
  DAT_011f38f4 = 0;
  FUN_00609340(0,iVar3,uVar1);
  FUN_00609810(1);
  FUN_0053d470(1);
  FUN_0053d590();
  FUN_0053d310();
  puVar5 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
  uVar2 = DAT_00e2eff4;
  uVar1 = DAT_00e2b1a4;
  if (puVar5 != (undefined4 *)0x0) {
    *puVar5 = DAT_00e2eff4;
    puVar5[1] = uVar2;
    puVar5[2] = uVar1;
    puVar5[3] = uVar2;
    puVar5[4] = uVar1;
    puVar5[5] = uVar1;
    puVar5[6] = uVar2;
    puVar5[7] = uVar1;
    FUN_0060cde0();
  }
  FUN_00612e00();
  if (param5 != '\\0') {
    FUN_00609890(1);
  }
  return;
}