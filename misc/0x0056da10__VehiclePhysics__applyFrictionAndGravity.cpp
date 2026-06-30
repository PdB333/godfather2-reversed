// FUNC_NAME: VehiclePhysics::applyFrictionAndGravity
void __fastcall VehiclePhysics::applyFrictionAndGravity(int thisPtr, float *param_2)
{
  float *pfVar1;
  int extraout_EDX;
  float *unaff_ESI;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined1 local_20 [28];
  
  fVar3 = 0.0;
  fVar4 = 0.0;
  fVar5 = 0.0;
  // DAT_00e44564 likely gravity constant (e.g., -9.81 or similar)
  // DAT_00e2b1a4 likely some friction/damping factor
  // param_2[0..3] are velocity components (x,y,z,w?) or maybe wheel speeds
  fVar6 = DAT_00e44564 -
          DAT_00e2b1a4 /
          (*param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2] +
          param_2[3] * param_2[3]);
  fVar2 = DAT_00e44564;
  FUN_00414aa0(); // likely getDeltaTime() or similar
  // +0x0C is some offset in the object (maybe velocity or position component)
  unaff_ESI[3] = fVar2 - *(float *)(extraout_EDX + 0xc);
  // Apply scaling factor to velocity components (friction/damping)
  *unaff_ESI = fVar6 * *unaff_ESI;
  unaff_ESI[1] = fVar6 * unaff_ESI[1];
  unaff_ESI[2] = fVar6 * unaff_ESI[2];
  unaff_ESI[3] = fVar6 * unaff_ESI[3];
  // Compute position delta from velocity
  local_30 = fVar2 - *unaff_ESI;
  local_2c = fVar2 - unaff_ESI[1];
  local_28 = fVar2 - unaff_ESI[2];
  local_24 = unaff_ESI[3];
  FUN_0056cba0(); // likely transform or integrate position
  pfVar1 = unaff_ESI + 4; // +0x10 offset (maybe angular velocity or acceleration)
  FUN_0056cba0(local_20,&local_30,pfVar1);
  // Negate angular component (friction on rotation)
  *pfVar1 = 0.0 - *pfVar1;
  unaff_ESI[5] = fVar3 - unaff_ESI[5];
  unaff_ESI[6] = fVar4 - unaff_ESI[6];
  unaff_ESI[7] = fVar5 - unaff_ESI[7];
  unaff_ESI[7] = 0.0;
  return;
}