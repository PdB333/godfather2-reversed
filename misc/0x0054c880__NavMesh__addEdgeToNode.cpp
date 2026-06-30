// FUNC_NAME: NavMesh::addEdgeToNode
void __thiscall NavMesh::addEdgeToNode(int thisPtr, undefined4 *edgeData)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  iVar1 = *(int *)(thisPtr + 0x14); // +0x14: current edge count
  FUN_0054c540(edgeData); // validate edge data
  if (*(int *)(thisPtr + 0x14) != iVar1) {
    iVar1 = *(int *)(thisPtr + 0x10); // +0x10: edge array base
    iVar4 = *(int *)(thisPtr + 0x14) * 0x30; // edge size = 0x30 bytes
    *(undefined4 *)(iVar4 + -0x30 + iVar1) = *edgeData;
    iVar1 = iVar4 + -0x30 + iVar1;
    *(undefined4 *)(iVar1 + 4) = edgeData[1];
    *(undefined4 *)(iVar1 + 8) = edgeData[2];
    *(undefined4 *)(iVar1 + 0xc) = edgeData[3];
    *(undefined4 *)(iVar1 + 0x10) = edgeData[4];
    *(undefined4 *)(iVar1 + 0x14) = edgeData[5];
    *(undefined4 *)(iVar1 + 0x18) = edgeData[6];
    *(undefined4 *)(iVar1 + 0x1c) = edgeData[7];
    iVar4 = edgeData[8];
    for (iVar3 = *(int *)(edgeData[8] + 0xc); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0xc)) {
      iVar4 = iVar3;
    }
    *(int *)(iVar1 + 0x20) = iVar4; // +0x20: linked node pointer
    iVar4 = edgeData[9];
    for (iVar3 = *(int *)(edgeData[9] + 0xc); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0xc)) {
      iVar4 = iVar3;
    }
    *(int *)(iVar1 + 0x28) = iVar4; // +0x28: linked node pointer
    uVar5 = *(uint *)(edgeData[9] + 4) & 0x3fffffff;
    *(uint *)(iVar1 + 0x2c) = uVar5; // +0x2c: edge flags
    if (*(int *)(*(int *)edgeData[9] + 0xc) == 4) {
      *(uint *)(iVar1 + 0x2c) = uVar5 | 0x80000000;
      piVar2 = (int *)edgeData[9];
      iVar4 = *piVar2;
      fVar8 = *(float *)(iVar4 + 0x44) - *(float *)(iVar4 + 0x34);
      fVar10 = *(float *)(iVar4 + 0x48) - *(float *)(iVar4 + 0x38);
      fVar9 = *(float *)(iVar4 + 0x34) - *(float *)(iVar4 + 0x24);
      fVar7 = *(float *)(iVar4 + 0x38) - *(float *)(iVar4 + 0x28);
      fVar11 = *(float *)(iVar4 + 0x30) - *(float *)(iVar4 + 0x20);
      fVar12 = *(float *)(iVar4 + 0x40) - *(float *)(iVar4 + 0x30);
      local_18 = fVar8 * fVar11 - fVar9 * fVar12;
      local_1c = fVar7 * fVar12 - fVar10 * fVar11;
      local_20 = fVar10 * fVar9 - fVar8 * fVar7;
      fVar7 = local_18 * local_18 + local_1c * local_1c + local_20 * local_20;
      if (fVar7 <= _DAT_00e448e0) {
        local_20 = 0.0;
        local_1c = DAT_00e2b1a4;
        local_18 = 0.0;
        local_14 = 0.0;
      }
      else {
        fVar6 = (float10)FUN_00414a80(fVar7); // sqrt
        fVar6 = (float10)1 / fVar6;
        local_20 = (float)((float10)local_20 * fVar6);
        local_1c = (float)((float10)local_1c * fVar6);
        local_18 = (float)((float10)local_18 * fVar6);
        local_14 = (float)(fVar6 * (float10)DAT_00e2b05c);
      }
      FUN_00aa2cd0(piVar2[2], &local_20); // set normal
      if (*(float *)(iVar1 + 0x18) * local_18 + *(float *)(iVar1 + 0x14) * local_1c +
          *(float *)(iVar1 + 0x10) * local_20 < 0.0) {
        local_20 = DAT_00e44564 - local_20;
        local_1c = DAT_00e44564 - local_1c;
        local_18 = DAT_00e44564 - local_18;
      }
      if (_DAT_00e448dc <
          *(float *)(iVar1 + 0x18) * local_18 + *(float *)(iVar1 + 0x14) * local_1c +
          *(float *)(iVar1 + 0x10) * local_20) {
        *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) & 0x3fffffff | 0x40000000;
      }
    }
  }
  return;
}