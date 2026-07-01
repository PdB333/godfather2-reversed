// FUNC_NAME: CoverHintNodeManager::evaluateCoverNodes
void __thiscall CoverHintNodeManager::evaluateCoverNodes(int this, int coverNodeArray, float count, int param4, int param5, float param6)
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 local_4;
  
  iVar3 = coverNodeArray;
  if (count != 0.0) {
    coverNodeArray = (int)count;
    do {
      uVar4 = 0;
      count = DAT_00d8b374; // Some global threshold value
      if (((param5 < 0) ||
          (cVar2 = FUN_00943210(*(undefined4 *)(param5 * 0x80 + 0x10 + this), // +0x10: some array element
                                *(undefined4 *)(param5 * 0x80 + this + 0x80), // +0x80: another array element
                                coverNodeArray + 0x10,
                                &count,0), cVar2 == '\0')) || (count < param6)) {
        iVar6 = 0;
        piVar5 = (int *)(this + 0x10); // +0x10: array of cover nodes
        do {
          if (((iVar6 != param5) && (iVar1 = *piVar5, iVar1 != 0)) &&
             ((*(int *)(iVar1 + 0x90) != 0 && (piVar5[0x1c] == 1)))) { // +0x90: some flag, +0x70 (0x1c*4): type
            local_4 = 0;
            cVar2 = FUN_00943210(iVar1,piVar5[0x1c],coverNodeArray + 0x10,&local_4,0);
            if (cVar2 != '\0') {
              uVar4 = 1;
              if (*(float *)(coverNodeArray + 0x14) < *(float *)(param4 + 4) || // +0x14: some distance/angle
                  *(float *)(coverNodeArray + 0x14) == *(float *)(param4 + 4)) {
                uVar4 = 3;
              }
              break;
            }
          }
          iVar6 = iVar6 + 1;
          piVar5 = piVar5 + 0x20;
        } while (iVar6 < 0x40); // 64 iterations (0x40)
      }
      else {
        uVar4 = 2;
      }
      *(undefined4 *)(coverNodeArray + 0x20) = uVar4; // +0x20: result/status
      coverNodeArray = coverNodeArray + 0x30; // 0x30 bytes per cover node entry
      coverNodeArray = coverNodeArray + -1;
    } while (coverNodeArray != 0);
  }
  return;
}