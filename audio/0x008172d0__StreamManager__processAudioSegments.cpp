// FUNC_NAME: StreamManager::processAudioSegments
void __thiscall StreamManager::processAudioSegments(int *this, uint startOffset, uint param3, int maxSegments)
{
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int local_10;
  int local_c;
  undefined4 local_8;
  code *local_4;
  
  uVar6 = param3 / (uint)this[5];  // +0x14 segmentSize
  iVar10 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  param3 = startOffset;
  uVar9 = 0;
  if (this[2] != 0) {  // +0x08 numSegments?
    do {
      uVar1 = param3;
      if (iVar10 == maxSegments) {
        uVar8 = local_c * uVar6;
        piVar3 = (int *)*this;  // +0x00 segmentBuffer
        iVar10 = piVar3[2];  // bufferCapacity
        if (piVar3[1] == iVar10) {  // bufferCount == capacity
          if (iVar10 == 0) {
            iVar10 = 1;
          }
          else {
            iVar10 = iVar10 * 2;
          }
          FUN_00817000(iVar10);  // resizeBuffer
        }
        puVar2 = (uint *)(*piVar3 + piVar3[1] * 0x18);  // 0x18 = segment size
        piVar3[1] = piVar3[1] + 1;  // increment count
        if (puVar2 != (uint *)0x0) {
          *puVar2 = uVar1;  // start offset
          puVar2[1] = uVar8;  // duration
          FUN_004d3b50(&local_10);  // registerCallback
        }
        FUN_004d3f10(0,0,0);  // resetState?
        param3 = param3 + uVar8;
        startOffset = 0;
        iVar10 = 0;
      }
      iVar7 = *(int *)(this[1] + uVar9 * 4);  // +0x04 segmentTable
      uVar1 = uVar9 + 1;
      if (uVar1 < (uint)this[2]) {
        FUN_004d43f0(iVar7,0,*(int *)(this[1] + uVar9 * 4 + 4) - iVar7);  // loadSegmentData
      }
      else {
        FUN_004d4300(iVar7);  // finalizeSegment
      }
      uVar8 = param3;
      iVar10 = iVar10 + 1;
      uVar9 = uVar1;
    } while (uVar1 < (uint)this[2]);
    if (iVar10 != 0) {
      uVar9 = local_c * uVar6;
      piVar3 = (int *)*this;
      iVar7 = piVar3[2];
      if (piVar3[1] == iVar7) {
        if (iVar7 == 0) {
          iVar7 = 1;
        }
        else {
          iVar7 = iVar7 * 2;
        }
        FUN_00817000(iVar7);
      }
      puVar2 = (uint *)(*piVar3 + piVar3[1] * 0x18);
      piVar3[1] = piVar3[1] + 1;
      if (puVar2 != (uint *)0x0) {
        *puVar2 = uVar8;
        puVar2[1] = uVar9;
        FUN_004d3b50(&local_10);
      }
      if (iVar10 == 1) {
        iVar4 = ((int *)*this)[1];
        iVar10 = *(int *)*this;
        iVar7 = iVar10 + -0x18 + iVar4 * 0x18;
        cVar5 = FUN_00816e70(iVar7 + 8,&param3,&startOffset);  // checkMergeSegments
        if (cVar5 != '\0') {
          iVar10 = iVar10 + (iVar4 * 3 + -6) * 8;
          if (param3 == 0) {
            piVar3 = (int *)(iVar10 + 4);
            *piVar3 = *piVar3 + *(int *)(iVar7 + 4);  // merge duration
            FUN_008170f0(*(int *)(*this + 4) + -1);  // removeSegment
          }
          else if (startOffset < 7) {
            FUN_00816f30(7 - startOffset,iVar10,iVar7,uVar6);  // shiftSegmentData
          }
        }
      }
    }
    if (local_10 != 0) {
      (*local_4)(local_10);  // executeCallback
    }
  }
  return;
}