// FUNC_NAME: Partition::moveMedianToPivotAndPartition
void Partition::moveMedianToPivotAndPartition(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1 != param_2) && (iVar3 = param_1 + 8, iVar3 != param_2)) {
    iVar4 = param_1 + 0x10;
    do {
      iVar1 = iVar3;
      if (*(float *)(param_1 + 4) <= *(float *)(iVar4 + -4)) {
        do {
          iVar2 = iVar1;
          iVar1 = iVar2 + -8;
        } while (*(float *)(iVar4 + -4) < *(float *)(iVar2 + -4));
        if (iVar2 != iVar3) goto joined_r0x0087d9cb;
      }
      else {
        iVar2 = param_1;
        if (param_1 != iVar3) {
joined_r0x0087d9cb:
          if (iVar3 != iVar4) {
            FUN_008760d0(iVar2,iVar3,iVar4,0,0);
          }
        }
      }
      iVar3 = iVar3 + 8;
      iVar4 = iVar4 + 8;
    } while (iVar3 != param_2);
  }
  return;
}