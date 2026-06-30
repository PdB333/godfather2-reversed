// FUNC_NAME: VehicleDamageComponent::setupResilienceValues
void __thiscall VehicleDamageComponent::setupResilienceValues(float param_1)
{
  int in_EAX;
  float *unaff_ESI;
  double dVar1;
  double dVar2;
  float fVar3;
  
  fVar3 = DAT_00e2b1a4; // global resilience base value
  *unaff_ESI = DAT_00e2b1a4;
  unaff_ESI[1] = 0.0;
  unaff_ESI[2] = 0.0;
  unaff_ESI[3] = 0.0;
  unaff_ESI[4] = 0.0;
  unaff_ESI[5] = fVar3;
  unaff_ESI[6] = 0.0;
  unaff_ESI[7] = 0.0;
  unaff_ESI[8] = 0.0;
  unaff_ESI[9] = 0.0;
  unaff_ESI[10] = fVar3;
  unaff_ESI[0xb] = 0.0;
  dVar2 = (double)param_1;
  if (in_EAX == 0) {
    // Front damage zone
    FUN_00b99fcb(); // likely getFrontDamageMultiplier or computeBaseEffect
    unaff_ESI[6] = (float)dVar2; // +0x18 (front elasticity?)
    dVar1 = (double)param_1;
    FUN_00b99e20(); // likely getRearDamageMultiplier
    unaff_ESI[9] = DAT_00e44564 - (float)dVar2; // +0x24 (rear elasticity = base - front)
    unaff_ESI[10] = (float)dVar1; // +0x28
    unaff_ESI[5] = (float)dVar1; // +0x14
    return;
  }
  if (in_EAX == 1) {
    // Rear damage zone
    FUN_00b99fcb();
    unaff_ESI[8] = (float)dVar2; // +0x20 (rear resistance)
    dVar1 = (double)param_1;
    FUN_00b99e20();
    fVar3 = DAT_00e44564 - (float)dVar2; // global base - rear resistance
    unaff_ESI[10] = (float)dVar1; // +0x28
    unaff_ESI[2] = fVar3; // +0x08 (front base?)
    *unaff_ESI = (float)dVar1; // +0x00
    return;
  }
  // Default: side damage zone
  FUN_00b99fcb();
  unaff_ESI[1] = (float)dVar2; // +0x04 (side resistance)
  dVar1 = (double)param_1;
  FUN_00b99e20();
  fVar3 = DAT_00e44564 - (float)dVar2; // global base - side resistance
  *unaff_ESI = (float)dVar1; // +0x00
  unaff_ESI[4] = fVar3; // +0x10
  unaff_ESI[5] = (float)dVar1; // +0x14
  return;
}