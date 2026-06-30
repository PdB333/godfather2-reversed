// FUNC_NAME: waitForConditionWithTimeout
uint waitForConditionWithTimeout(uint *param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar3 = FUN_0065c190(); // getCurrentTimeMs
  uVar5 = *param_1;
  do {
    uVar1 = uVar5 + 50000;
    for (; uVar5 < uVar1; uVar5 = uVar5 + 1) {
      cVar2 = FUN_0065cae0(param_2,param_3,param_4); // checkCondition
      if (cVar2 != '\0') {
        *param_1 = uVar5;
        return 1;
      }
    }
    iVar4 = FUN_0065c190(); // getCurrentTimeMs
  } while ((uint)(iVar4 - iVar3) < 0x1f); // 31ms timeout
  *param_1 = uVar5;
  return 0;
}