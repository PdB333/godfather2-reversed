// FUNC_NAME: StringTable::findString
byte * __fastcall StringTable::findString(int thisPtr, int param_2, byte *param_3)
{
  uint uVar1;
  code *pcVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  
  param_2 = param_2 + -0x31;
  if (((param_2 < 0) || (*(int *)(in_EAX + 0xc) <= param_2)) ||
     (uVar1 = *(uint *)(in_EAX + 0x14 + param_2 * 8), uVar1 == 0xffffffff)) {
    FUN_00627bd0("invalid capture index");
    pcVar2 = (code *)swi(3);
    pbVar6 = (byte *)(*pcVar2)();
    return pbVar6;
  }
  if ((uint)(*(int *)(in_EAX + 4) - (int)param_3) < uVar1) {
    return (byte *)0x0;
  }
  pbVar6 = *(byte **)(in_EAX + 0x10 + param_2 * 8);
  pbVar5 = param_3;
  for (uVar3 = uVar1; 3 < uVar3; uVar3 = uVar3 - 4) {
    if (*(int *)pbVar6 != *(int *)pbVar5) goto LAB_0062bcdb;
    pbVar5 = pbVar5 + 4;
    pbVar6 = pbVar6 + 4;
  }
  if (uVar3 == 0) {
LAB_0062bd38:
    iVar4 = 0;
  }
  else {
LAB_0062bcdb:
    iVar7 = (uint)*pbVar6 - (uint)*pbVar5;
    if (iVar7 == 0) {
      if (uVar3 == 1) goto LAB_0062bd38;
      iVar7 = (uint)pbVar6[1] - (uint)pbVar5[1];
      if (iVar7 == 0) {
        if (uVar3 == 2) goto LAB_0062bd38;
        iVar7 = (uint)pbVar6[2] - (uint)pbVar5[2];
        if (iVar7 == 0) {
          if ((uVar3 == 3) || (iVar7 = (uint)pbVar6[3] - (uint)pbVar5[3], iVar7 == 0))
          goto LAB_0062bd38;
        }
      }
    }
    iVar4 = 1;
    if (iVar7 < 1) {
      iVar4 = -1;
    }
  }
  if (iVar4 != 0) {
    return (byte *)0x0;
  }
  return param_3 + uVar1;
}