// FUNC_NAME: Vehicle::computeSpeedBasedDamage
int __fastcall Vehicle::computeSpeedBasedDamage(int this)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float local_1c;
  float fStack_18;
  float fStack_14;
  
  iVar3 = *(int *)(this + 0x7c); // +0x7c: baseDamage
  if ((((*(uint *)(this + 0xa8) >> 9 & 1) != 0) && (**(int **)(DAT_012233a0 + 4) != 0)) &&
     (piVar1 = (int *)(**(int **)(DAT_012233a0 + 4) + -0x1f30), piVar1 != (int *)0x0)) {
    cVar2 = (**(code **)(*piVar1 + 0x28c))(); // check if player is in vehicle
    if (cVar2 != '\0') {
      iVar3 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2; // divide by 4 (damage reduction for player)
    }
  }
  FUN_0083b990(&local_1c); // get vehicle velocity vector
  fVar5 = 0.0;
  fVar4 = SQRT(fStack_14 * fStack_14 + local_1c * local_1c + fStack_18 * fStack_18) - DAT_00d68260; // speed - minDamageSpeed
  if (0.0 < fVar4) {
    if (DAT_00d742ec < fVar4) {
      fVar4 = DAT_00d742ec; // clamp to maxDamageSpeed
    }
    fVar5 = fVar4 * _DAT_00d742e8; // speedDamageMultiplier
  }
  iVar3 = iVar3 - ((int)((float)iVar3 * *(float *)(this + 0x88) * fVar5 + _DAT_00d5c458) +
                  *(int *)(this + 0x8c)); // +0x88: damageReductionFactor, +0x8c: flatDamageReduction
  if (iVar3 < 0) {
    return 0;
  }
  return iVar3;
}