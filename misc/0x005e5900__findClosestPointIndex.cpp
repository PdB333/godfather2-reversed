// FUNC_NAME: findClosestPointIndex
uint findClosestPointIndex(int param_1) // param_1 likely a pointer to output distances array
{
  float fVar1;
  float fVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  int unaff_ESI; // pointer to an array of 3D vectors (points)
  uint unaff_EDI; // number of points in the array
  float fVar6;
  float fVar7;
  
  uVar3 = 0;
  if (unaff_ESI != 0) {
    bVar5 = 0;
    if (unaff_EDI != 0) {
      uVar4 = 0;
      fVar7 = DAT_00e2e50c; // some maximum distance initializer, maybe FLOAT_MAX or a large constant
      do {
        fVar6 = *(float *)(unaff_ESI + 8 + uVar4 * 0xc); // point Z coordinate (offset +8 from base, stride 0xC = 12 bytes)
        fVar1 = *(float *)(unaff_ESI + 4 + uVar4 * 0xc); // point Y coordinate (offset +4)
        fVar2 = *(float *)(unaff_ESI + uVar4 * 0xc);     // point X coordinate (offset +0)
        fVar6 = SQRT(fVar6 * fVar6 + fVar1 * fVar1 + fVar2 * fVar2); // compute distance from origin (or from reference point? assuming origin)
        *(float *)(param_1 + uVar4 * 4) = fVar6; // store distance in output array
        if (fVar6 < fVar7) {
          uVar3 = uVar4;     // track index of closest point
          fVar7 = fVar6;     // update minimum distance
        }
        bVar5 = bVar5 + 1;   // increment byte counter
        uVar4 = (uint)bVar5; // cast to uint for loop
      } while (uVar4 < unaff_EDI); // loop until all points processed
    }
  }
  return uVar3; // return index of point with smallest distance (closest to origin)
}