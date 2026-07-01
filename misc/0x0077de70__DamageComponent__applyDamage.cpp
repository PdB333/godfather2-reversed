// FUNC_NAME: DamageComponent::applyDamage
void __thiscall DamageComponent::applyDamage(int this, int damageInfo, int targetEntity)
{
  float fVar1;
  byte bVar2;
  int iVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  
  // Check if damage type is 0x25 (explosion?) and target is valid
  bVar2 = (byte)(*(uint *)(damageInfo + 0x80) >> 1) & 1;
  if ((((*(int *)(damageInfo + 0x54) == 0x25) && (targetEntity != 0)) 
      && (*(int *)(targetEntity + 0x22c8) != 0))
     && (*(int *)(targetEntity + 0x22c8) != 0x48)) {
    if (*(int *)(targetEntity + 0x22c8) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(targetEntity + 0x22c8) + -0x48;
    }
    bVar2 = (byte)(*(uint *)(iVar3 + 0x110) >> 5) & 1;
  }
  
  if (bVar2 == 0) {
    // Get damage direction vector
    pfVar4 = (float *)FUN_0077e930(targetEntity);
    fVar1 = DAT_00d68ebc; // Some max damage threshold
    
    // Accumulate damage components (positional damage?)
    *(float *)(this + 4) = *pfVar4 + *(float *)(this + 4);
    fVar6 = *(float *)(this + 4);
    *(float *)(this + 8) = pfVar4[1] + *(float *)(this + 8);
    *(float *)(this + 0xc) = pfVar4[2] + *(float *)(this + 0xc);
    *(float *)(this + 0x10) = pfVar4[3] + *(float *)(this + 0x10);
    
    // Clamp damage values between 0 and max
    if (0.0 < fVar6) {
      if (fVar1 <= fVar6) {
        fVar6 = fVar1;
      }
    }
    else {
      fVar6 = 0.0;
    }
    *(float *)(this + 4) = fVar6;
    
    fVar6 = *(float *)(this + 8);
    if (0.0 < fVar6) {
      if (fVar1 <= fVar6) {
        fVar6 = fVar1;
      }
    }
    else {
      fVar6 = 0.0;
    }
    *(float *)(this + 8) = fVar6;
    
    fVar6 = *(float *)(this + 0xc);
    if (0.0 < fVar6) {
      if (fVar1 <= fVar6) {
        fVar6 = fVar1;
      }
    }
    else {
      fVar6 = 0.0;
    }
    *(float *)(this + 0xc) = fVar6;
    
    fVar6 = *(float *)(this + 0x10);
    fVar5 = 0.0;
    if ((0.0 < fVar6) && (fVar5 = fVar6, fVar1 <= fVar6)) {
      *(float *)(this + 0x10) = fVar1;
      FUN_0077dac0(damageInfo);
      return;
    }
    *(float *)(this + 0x10) = fVar5;
  }
  
  FUN_0077dac0(damageInfo);
  return;
}