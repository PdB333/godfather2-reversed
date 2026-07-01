// FUNC_NAME: Animated::processAnimationJobs
char __thiscall Animated::processAnimationJobs(int *this, int param_2)
{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint numElements;
  undefined1 *puVar8;
  char cVar9;
  int iVar10;
  undefined4 *puVar11;
  float10 fVar12;
  char local_19;
  int local_18;
  uint local_10;
  
  fVar3 = *(float *)(param_2 + 0x18);  // +0x18: animation speed
  uVar4 = *(undefined4 *)(param_2 + 0x1c);  // +0x1c: animation frame data
  uVar2 = *(undefined4 *)(DAT_0122349c + 0x34);  // global timer
  local_19 = '\0';
  
  // Push graphics state
  FUN_004899b0(*(undefined4 *)(param_2 + 0x10));  // +0x10: bone matrix
  FUN_00489a00(*(undefined4 *)(param_2 + 0x14));  // +0x14: bone weights
  FUN_0048c0f0(uVar4);  // set animation frame
  
  fVar12 = (float10)FUN_0048be00();  // get frame delta
  local_18 = *(int *)(*this + 4) + -1;  // job count - 1
  local_10 = (uint)(longlong)ROUND((float10)*(float *)(param_2 + 0xc) / (fVar12 * (float10)fVar3));  // blend steps
  
  cVar9 = '\0';
  if (-1 < local_18) {
    iVar10 = local_18 * 0x18;
    do {
      puVar11 = (undefined4 *)(*(int *)*this + iVar10);  // +0x18 per job struct
      FUN_004d3e20(puVar11 + 2);  // process blend weight
      puVar8 = (undefined1 *)puVar11[2];  // animation name
      if (puVar8 == (undefined1 *)0x0) {
        puVar8 = &DAT_0120546e;
      }
      FUN_0068fdb0(puVar8,this + 4,1);  // load animation
      this[2] = 0;  // current frame
      FUN_009c8f10(this[1]);  // free previous
      this[1] = 0;
      this[3] = 0;  // blend factor
      FUN_00817170(*(undefined4 *)(param_2 + 8),fVar3);  // update skeleton
      if (local_10 < (uint)this[2]) {
        FUN_008172d0(*puVar11,puVar11[1],local_10);  // apply animation to bones
        piVar5 = (int *)*this;
        iVar6 = piVar5[1];
        if (local_18 != iVar6 + -1) {
          iVar7 = *piVar5;
          iVar1 = iVar7 + -0x18 + iVar6 * 0x18;
          *(undefined4 *)(iVar10 + iVar7) = *(undefined4 *)(iVar7 + -0x18 + iVar6 * 0x18);
          *(undefined4 *)(iVar10 + 4 + iVar7) = *(undefined4 *)(iVar1 + 4);
          FUN_004d3e20(iVar1 + 8);  // remove finished job
        }
        piVar5[1] = piVar5[1] + -1;
        piVar5 = (int *)(*piVar5 + 8 + piVar5[1] * 0x18);
        iVar6 = *piVar5;
        if (iVar6 != 0) {
          (*(code *)piVar5[3])(iVar6);  // call completion callback
        }
        local_19 = '\x01';
      }
      local_18 = local_18 + -1;
      iVar10 = iVar10 + -0x18;
      cVar9 = local_19;
    } while (-1 < local_18);
  }
  
  FUN_0048c0f0(uVar2);  // restore global timer
  if (cVar9 != '\0') {
    numElements = ((undefined4 *)*this)[1];  // element count
    if (1 < numElements) {
      _qsort(*(void **)*this,numElements,0x18,(_PtFuncCompare *)&LAB_00816bd0);  // sort jobs by key
    }
  }
  return cVar9;
}