// FUNC_NAME: ChaseCamera::computeDesiredPositionAndLookAt
void __thiscall ChaseCamera::computeDesiredPositionAndLookAt(int thisPtr, undefined8 *outLookAt, float *outPosition)
{
  char cVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  undefined8 localLookAt;
  undefined4 localLookAt_hi;
  float localDeltaX;
  float localDeltaY;
  float localDeltaZ;
  undefined4 localPad;
  
  FUN_00875190(&localLookAt, 0); // Initialize lookAt to zero
  pfVar3 = (float *)0x0;
  if ((*(int *)(thisPtr + 0x10d8) != 0) && (*(float **)(thisPtr + 0x10e0) != (float *)0x0)) {
    pfVar3 = *(float **)(thisPtr + 0x10e0); // +0x10e0: target position pointer
  }
  pfVar4 = (float *)0x0;
  if ((*(int *)(thisPtr + 0x10cc) != 0) && (*(float **)(thisPtr + 0x10d4) != (float *)0x0)) {
    pfVar4 = *(float **)(thisPtr + 0x10d4); // +0x10d4: camera position pointer
  }
  if ((pfVar3 == (float *)0x0) || (pfVar4 == (float *)0x0)) {
    // Fallback: use default lookAt and position from global
    *outLookAt = localLookAt;
    *(undefined4 *)(outLookAt + 1) = localLookAt_hi;
    iVar2 = FUN_00471610(); // Get default camera data
    *(undefined8 *)outPosition = *(undefined8 *)(iVar2 + 0x20);
    outPosition[2] = *(float *)(iVar2 + 0x28);
  }
  else {
    // Compute delta from camera to target
    localDeltaX = *pfVar3 - *pfVar4;
    localDeltaY = pfVar3[1] - pfVar4[1];
    localDeltaZ = pfVar3[2] - pfVar4[2];
    localPad = 0;
    FUN_0056afa0(&localDeltaX, &localDeltaX); // Normalize delta
    *outPosition = localDeltaX;
    outPosition[1] = localDeltaY;
    outPosition[2] = localDeltaZ;
    cVar1 = FUN_004a08d0(outLookAt, &localLookAt, pfVar4, pfVar3); // Compute lookAt from camera to target
    if (((cVar1 == '\\0') && (*(int *)(thisPtr + 0x10c0) != 0)) &&
       (pfVar3 = *(float **)(thisPtr + 0x10c8), pfVar3 != (float *)0x0)) {
      // Additional offset from another reference point
      localDeltaX = *pfVar4 - *pfVar3;
      localDeltaY = pfVar4[1] - pfVar3[1];
      localDeltaZ = pfVar4[2] - pfVar3[2];
      FUN_0043a210(outPosition, &localDeltaX); // Add offset to position
      FUN_004a08d0(outLookAt, &localLookAt, pfVar3, pfVar4); // Recompute lookAt
      return;
    }
  }
  return;
}