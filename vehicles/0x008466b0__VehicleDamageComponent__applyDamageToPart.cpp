// FUNC_NAME: VehicleDamageComponent::applyDamageToPart
void __thiscall VehicleDamageComponent::applyDamageToPart(int this, int *damageType, undefined4 *damageResult)
{
  int damageTypeId;
  
  damageTypeId = *damageType;
  if (damageTypeId == DAT_0120678c) {
    if (this == 0) {
      this = 0;
    }
    else {
      this = this + 0x3c; // +0x3c: offset to part health or damage multiplier
    }
    FUN_004035f0(*damageResult,0x100,this); // likely setDamage or applyDamage with type 0x100
    return;
  }
  if ((damageTypeId == DAT_01206778) || (damageTypeId == DAT_01206780)) {
    if (this == 0) {
      this = 0;
    }
    else {
      this = this + 0x3c; // +0x3c: offset to part health or damage multiplier
    }
    FUN_004035f0(*damageResult,0x114,this); // different damage type (0x114)
    *damageResult = 0; // clear result after applying
  }
  return;
}