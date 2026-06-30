// FUNC_NAME: SpatialQuery::findNearestPoints
void SpatialQuery::findNearestPoints(float *queryPos, int *callbackFunc, int *thresholdDistSq)
{
  char cVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  float *pfVar7;
  int *piVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  int iVar12;
  
  cVar1 = (**(code **)(*thresholdDistSq + 4))(queryPos); // vtable call: isQueryValid?
  if (cVar1 != '\0') {
    uVar3 = *(ushort *)(queryPos + 3); // +0x0C: numPoints
    fVar11 = 0.0;
    cVar1 = '\0';
    iVar12 = -1;
    uVar5 = 0;
    piVar8 = thresholdDistSq;
    if (uVar3 != 0) {
      do {
        if (cVar1 != '\0') {
          return;
        }
        uVar2 = (uint)uVar3;
        iVar6 = -1;
        fVar10 = DAT_00e2e50c; // FLT_MAX constant
        if (uVar3 != 0) {
          iVar4 = 0;
          pfVar7 = (float *)queryPos[8]; // +0x20: points array
          do {
            fVar9 = (pfVar7[1] - queryPos[1]) * (pfVar7[1] - queryPos[1]) +
                    (*pfVar7 - *queryPos) * (*pfVar7 - *queryPos) +
                    (pfVar7[2] - queryPos[2]) * (pfVar7[2] - queryPos[2]); // distance squared
            if (fVar9 <= fVar11) {
              if ((fVar9 == fVar11) && (iVar12 < iVar4)) goto LAB_00602175;
            }
            else if (fVar9 < fVar10) {
LAB_00602175:
              iVar6 = iVar4;
              fVar10 = fVar9;
            }
            iVar4 = iVar4 + 1;
            pfVar7 = pfVar7 + 9; // stride of 9 floats per point (x,y,z + 6 unknown)
            uVar2 = uVar2 - 1;
            piVar8 = callbackFunc;
          } while (uVar2 != 0);
        }
        if (fVar10 <= (float)thresholdDistSq) {
          cVar1 = (**(code **)*piVar8)(queryPos, (float *)queryPos[8] + iVar6 * 9, queryPos); // callback on nearest point
        }
        else {
          cVar1 = '\x01'; // stop searching
        }
        uVar3 = *(ushort *)(queryPos + 3); // +0x0C: numPoints
        uVar5 = uVar5 + 1;
        fVar11 = fVar10;
        iVar12 = iVar6;
      } while (uVar5 < uVar3);
    }
  }
  return;
}