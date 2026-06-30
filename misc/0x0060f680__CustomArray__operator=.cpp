// FUNC_NAME: CustomArray::operator=
int* CustomArray::operator=(int* param_1, int* param_2)
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if (param_1 != param_2) {
    iVar3 = param_1[1] + -1;
    if (-1 < iVar3) {
      iVar4 = iVar3 * 0x14;
      do {
        iVar1 = *(int *)(iVar4 + 8 + *param_1);
        if (iVar1 != 0) {
          operator_delete(iVar1);         // FUN_009c8f10
        }
        iVar3 = iVar3 + -1;
        iVar4 = iVar4 + -0x14;
      } while (-1 < iVar3);
    }
    if ((uint)param_1[2] < (uint)param_2[1]) {
      operator_delete(*param_1);           // FUN_009c8f10
      iVar3 = param_2[1];
      param_1[2] = iVar3;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = operator_new(iVar3 * 0x14); // FUN_009c8e80
      }
      *param_1 = iVar3;
    }
    if (param_2[1] != 0) {
      iVar3 = 0;
      uVar5 = 0;
      do {
        puVar2 = (undefined4 *)(*param_1 + iVar3);
        if (puVar2 != (undefined4 *)0x0) {
          iVar4 = *param_2 + iVar3;
          *puVar2 = *(undefined4 *)(*param_2 + iVar3);
          puVar2[1] = *(undefined4 *)(iVar4 + 4);
          element_partial_copy(iVar4 + 8); // FUN_006099f0 copy subobject at offset 8
        }
        uVar5 = uVar5 + 1;
        iVar3 = iVar3 + 0x14;
      } while (uVar5 < (uint)param_2[1]);
    }
    param_1[1] = param_2[1];
  }
  return param_1;
}