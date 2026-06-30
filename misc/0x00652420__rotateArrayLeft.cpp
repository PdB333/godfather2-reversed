// FUNC_NAME: rotateArrayLeft
void rotateArrayLeft(undefined4 *param_1, undefined4 *param_2)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int in_EAX;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  
  iVar7 = (int)param_2 - (int)param_1 >> 2;
  iVar5 = in_EAX - (int)param_1 >> 2;
  iVar8 = iVar5;
  iVar6 = iVar7;
  while (iVar2 = iVar8, iVar2 != 0) {
    iVar8 = iVar6 % iVar2;
    iVar6 = iVar2;
  }
  if ((iVar6 < iVar7) && (0 < iVar6)) {
    puVar9 = param_1 + iVar6;
    do {
      uVar1 = *puVar9;
      puVar4 = puVar9 + iVar5;
      puVar3 = puVar9;
      if (puVar9 + iVar5 == param_2) {
        puVar4 = param_1;
      }
      while (puVar4 != puVar9) {
        *puVar3 = *puVar4;
        iVar8 = (int)param_2 - (int)puVar4 >> 2;
        puVar3 = puVar4;
        if (iVar5 < iVar8) {
          puVar4 = puVar4 + iVar5;
        }
        else {
          puVar4 = param_1 + (iVar5 - iVar8);
        }
      }
      iVar6 = iVar6 + -1;
      puVar9 = puVar9 + -1;
      *puVar3 = uVar1;
    } while (0 < iVar6);
  }
  return;
}