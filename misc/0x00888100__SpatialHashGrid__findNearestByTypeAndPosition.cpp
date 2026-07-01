// FUNC_NAME: SpatialHashGrid::findNearestByTypeAndPosition
int __thiscall SpatialHashGrid::findNearestByTypeAndPosition(int this, uint typeId, float *position)
{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  uVar10 = 0;
  uVar9 = (*(int *)(this + 0xa0) - *(int *)(this + 0x9c)) >> 2; // number of entries in sorted array
  if (uVar9 != 0) {
    do {
      uVar7 = (uVar9 + uVar10) >> 1; // binary search midpoint
      // Compare typeId with the type stored at +0x60 in the object's data (+0x14 offset from entry)
      if (*(uint *)(*(int *)(*(int *)(*(int *)(this + 0x9c) + uVar7 * 4) + 0x14) + 0x60) < typeId) {
        uVar10 = uVar7 + 1;
        uVar7 = uVar9;
      }
      uVar9 = uVar7;
    } while (uVar10 < uVar7);
  }
  if (uVar10 < (uint)((*(int *)(this + 0xa0) - *(int *)(this + 0x9c)) >> 2)) {
    iVar6 = *(int *)(*(int *)(this + 0x9c) + uVar10 * 4); // candidate entry
    iVar11 = (int)(*(int *)(this + 0x9c) + uVar10 * 4); // pointer to entry in array
    if (typeId == *(uint *)(*(int *)(iVar6 + 0x14) + 0x60)) {
      fVar2 = position[1]; // Y
      fVar3 = *position;   // X
      fVar4 = position[2]; // Z
      iVar8 = *(int *)(iVar6 + 0x14); // object data pointer
      fVar13 = fVar2 - *(float *)(iVar8 + 0x18); // dy
      fVar12 = fVar3 - *(float *)(iVar8 + 0x14); // dx
      fVar15 = fVar4 - *(float *)(iVar8 + 0x1c); // dz
      iVar8 = iVar11;
      fVar12 = fVar15 * fVar15 + fVar13 * fVar13 + fVar12 * fVar12; // squared distance
      uVar9 = uVar10;
      // Search backwards for closer entries with same typeId
      while (uVar9 != 0) {
        piVar1 = (int *)(iVar8 + -4);
        iVar5 = *(int *)(*piVar1 + 0x14);
        iVar8 = iVar8 + -4;
        uVar9 = uVar9 - 1;
        if (*(uint *)(iVar5 + 0x60) != typeId) break;
        fVar14 = fVar2 - *(float *)(iVar5 + 0x18);
        fVar15 = fVar3 - *(float *)(iVar5 + 0x14);
        fVar13 = fVar4 - *(float *)(iVar5 + 0x1c);
        fVar13 = fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15;
        if (fVar13 < fVar12) {
          iVar6 = *piVar1;
          fVar12 = fVar13;
        }
      }
      if ((*(int *)(this + 0xa0) - *(int *)(this + 0x9c) >> 2) - 1U <= uVar10) {
        return iVar6;
      }
      // Search forwards for closer entries with same typeId
      do {
        piVar1 = (int *)(iVar11 + 4);
        iVar8 = *(int *)(*piVar1 + 0x14);
        iVar11 = iVar11 + 4;
        uVar10 = uVar10 + 1;
        if (*(uint *)(iVar8 + 0x60) != typeId) {
          return iVar6;
        }
        fVar14 = fVar2 - *(float *)(iVar8 + 0x18);
        fVar15 = fVar3 - *(float *)(iVar8 + 0x14);
        fVar13 = fVar4 - *(float *)(iVar8 + 0x1c);
        fVar13 = fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15;
        if (fVar13 < fVar12) {
          iVar6 = *piVar1;
          fVar12 = fVar13;
        }
      } while (uVar10 < (*(int *)(this + 0xa0) - *(int *)(this + 0x9c) >> 2) - 1U);
      return iVar6;
    }
  }
  return 0; // not found
}