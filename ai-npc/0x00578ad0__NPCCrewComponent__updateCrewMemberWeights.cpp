// FUNC_NAME: NPCCrewComponent::updateCrewMemberWeights
int* NPCCrewComponent::updateCrewMemberWeights(void)
{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  double dVar10;
  float local_24;
  int *local_18;
  
  // +0x74: some short field, reset to -1 initially
  *(undefined2 *)(in_EAX + 0x74) = 0xffff;
  uVar2 = FUN_00571070(); // likely getSomeFlag or getCurrentTime
  piVar3 = (int *)FUN_00581c60(in_EAX,uVar2); // getCrewMemberList or similar
  if (*(short *)(in_EAX + 0x74) == -1) {
    *(undefined2 *)(in_EAX + 0x74) = 0;
  }
  // +0x10: flags field, check bit 0x14 (some condition)
  if (((*(uint *)(in_EAX + 0x10) >> 0x14 & 1) != 0) || (iVar4 = FUN_00579170(), iVar4 == 0)) {
    return piVar3;
  }
  piVar7 = (int *)0x0;
  local_24 = 0.0;
  uVar5 = FUN_00571070(); // getCurrentTime again
  iVar4 = iVar4 + -1;
  piVar8 = piVar7;
  local_18 = (int *)uVar5;
  if (-1 < iVar4) {
    do {
      // +0x2e4: array size, +0x2e8: current index, +0x2ec: base pointer
      // Each element is 0xe0 bytes
      piVar9 = (int *)((((*(int *)(in_EAX + 0x2e4) - iVar4) + *(int *)(in_EAX + 0x2e8)) %
                       *(int *)(in_EAX + 0x2e4)) * 0xe0 + *(int *)(in_EAX + 0x2ec));
      // vtable call at +0xc: getWeight or getScore
      piVar6 = (int *)(**(code **)(*piVar9 + 0xc))();
      piVar7 = piVar6;
      if ((piVar8 != (int *)0x0) && (piVar7 = piVar8, DAT_00e2b05c < local_24)) {
        if (piVar6 == (int *)0x0) {
          local_18 = (int *)0x0;
        }
        else {
          local_18 = (int *)FUN_005848f0(piVar8,piVar6,local_24,local_18); // mergeWeights
        }
        FUN_0056fb60(); // releaseRef or decrementRefCount
        FUN_0056fb60(); // releaseRef again
        piVar7 = local_18;
      }
      // +0x1c (0x70 offset in 0xe0 struct): some byte flag
      if ((char)piVar9[0x1c] == '\\0') {
        local_24 = 0.0;
      }
      else {
        // +0x1e and +0x1f: some ratio fields
        dVar10 = (double)(((float)piVar9[0x1e] / (float)piVar9[0x1f]) * DAT_00e2afac - DAT_00e2a850);
        FUN_00b99fcb(); // sin or cos
        local_24 = ((float)dVar10 + DAT_00e2b1a4) * DAT_00e2cd54;
      }
      local_18 = (int *)uVar5;
      // +0x20 (0x80 offset): some type field
      if (piVar9[0x20] == 2) {
        local_18 = (int *)(uVar5 | 0x100);
      }
      iVar4 = iVar4 + -1;
      piVar8 = piVar7;
    } while (-1 < iVar4);
    if ((piVar7 != (int *)0x0) && (piVar3 != (int *)0x0)) {
      local_18 = (int *)FUN_005848f0(piVar7,piVar3,local_24,local_18);
      goto LAB_00578c84;
    }
  }
  local_18 = (int *)0x0;
LAB_00578c84:
  iVar4 = DAT_01205568; // global memory pool
  if (piVar7 != (int *)0x0) {
    FUN_0056f4b0(); // releaseRef
    *(char *)((int)piVar7 + 9) = *(char *)((int)piVar7 + 9) + -1;
    if (((char)piVar7[2] == '\\0') && (*(char *)((int)piVar7 + 9) == '\\0')) {
      iVar1 = *piVar7;
      piVar7 = (int *)piVar7[1];
      if (iVar1 != 0) {
        *(int **)(iVar1 + 4) = piVar7;
      }
      if (piVar7 == (int *)0x0) {
        *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 4);
        *(int *)(iVar4 + 4) = iVar1;
        if (iVar1 == 0) {
          *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 0xc);
        }
      }
      else {
        *piVar7 = iVar1;
      }
    }
  }
  if (piVar3 != (int *)0x0) {
    FUN_0056f4b0(); // releaseRef
    *(char *)((int)piVar3 + 9) = *(char *)((int)piVar3 + 9) + -1;
    if (((char)piVar3[2] == '\\0') && (*(char *)((int)piVar3 + 9) == '\\0')) {
      iVar1 = *piVar3;
      piVar3 = (int *)piVar3[1];
      if (iVar1 != 0) {
        *(int **)(iVar1 + 4) = piVar3;
      }
      if (piVar3 != (int *)0x0) {
        *piVar3 = iVar1;
        return local_18;
      }
      *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 4);
      *(int *)(iVar4 + 4) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(iVar4 + 0xc);
      }
    }
  }
  return local_18;
}