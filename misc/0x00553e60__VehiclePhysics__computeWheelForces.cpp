// FUNC_NAME: VehiclePhysics::computeWheelForces
void __thiscall VehiclePhysics::computeWheelForces(int this, int wheelData, float *outForces)
{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float local_8 [2];
  
  // Copy wheel local position from wheelData (offset +0x10, +0x14, +0x18, +0x1c)
  *outForces = *(float *)(wheelData + 0x10);
  fVar6 = *outForces;
  outForces[1] = *(float *)(wheelData + 0x14);
  local_8[0] = outForces[1];
  outForces[2] = *(float *)(wheelData + 0x18);
  fVar2 = outForces[2];
  outForces[3] = *(float *)(wheelData + 0x1c);
  
  // Normalize the direction vector
  fVar5 = fVar6 * fVar6 + local_8[0] * local_8[0] + fVar2 * fVar2;
  if (fVar5 == 0.0) {
    fVar5 = 0.0;
  }
  else {
    fVar4 = (float10)FUN_00414a80(fVar5);  // sqrt
    fVar5 = (float)((float10)1 / fVar4);   // 1/sqrt
  }
  outForces[2] = fVar2 * fVar5;
  *outForces = fVar6 * fVar5;
  outForces[1] = local_8[0] * fVar5;
  outForces[3] = outForces[3] * fVar5;
  
  // Restore original w component and compute suspension compression
  outForces[3] = *(float *)(wheelData + 0x1c);
  outForces[3] = outForces[3] - *(float *)(this + 0x58);  // chassis height offset
  
  // Copy vehicle state values
  outForces[8] = *(float *)(this + 0x38);   // vehicle velocity
  outForces[0xb] = *(float *)(this + 0x34);  // vehicle angular velocity
  outForces[9] = *(float *)(this + 0x50);    // vehicle forward direction
  pfVar1 = outForces + 4;
  outForces[10] = *(float *)(this + 0x54);   // vehicle right direction
  outForces[7] = 0.0;
  outForces[6] = 0.0;
  outForces[5] = 0.0;
  *pfVar1 = 0.0;
  outForces[0xc] = 0.0;
  
  // Check for wheel contact with ground
  iVar3 = *(int *)(wheelData + 0x28);
  if ((*(char *)(iVar3 + 0x18) == '\x01') && (iVar3 = *(char *)(iVar3 + 0x10) + iVar3, iVar3 != 0))
  {
    FUN_00552060(wheelData, pfVar1);  // compute wheel contact forces
    FUN_004af8c0(local_8, 0x2006);    // get ground material properties
    if (local_8[0] != 0.0) {
      *pfVar1 = *pfVar1 + *(float *)((int)local_8[0] + 0x20);  // friction force
      outForces[5] = *(float *)((int)local_8[0] + 0x24) + outForces[5];
      outForces[6] = *(float *)((int)local_8[0] + 0x28) + outForces[6];
      outForces[7] = *(float *)((int)local_8[0] + 0x2c) + outForces[7];
    }
    // Check surface type flags
    if (*(char *)(iVar3 + 0xd8) == '\a') {
      outForces[0xc] = 2.8026e-45;  // slippery surface flag
    }
    if (*(char *)(iVar3 + 0xd8) == '\x06') {
      outForces[0xc] = 1.4013e-45;  // icy surface flag
    }
  }
  
  // Apply suspension force if wheel is compressed beyond threshold
  if (outForces[3] < DAT_00e44778) {
    fVar6 = DAT_00e44564 - outForces[3];
    if (DAT_00e39f98 < fVar6) {
      fVar6 = DAT_00e39f98;
    }
    *pfVar1 = *(float *)(wheelData + 0x10) * fVar6 + *pfVar1;
    outForces[5] = *(float *)(wheelData + 0x14) * fVar6 + outForces[5];
    outForces[6] = *(float *)(wheelData + 0x18) * fVar6 + outForces[6];
    outForces[7] = *(float *)(wheelData + 0x1c) * fVar6 + outForces[7];
    outForces[3] = 0.0;
  }
  return;
}