// FUNC_NAME: Sentient::updateCombatBehavior
void __fastcall Sentient::updateCombatBehavior(int *this)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float local_18;
  float fStack_14;
  undefined4 uStack_10;
  float fStack_c;
  float fStack_8;
  
  // Check if any of the 4 combat state flags (offsets +0x2B0, +0x2B4, +0x2B8, +0x2BC) are non-zero
  // and not equal to specific sentinel values (likely "no target" markers)
  if (((((this[0xac] != 0) || (this[0xad] != 0)) || (this[0xae] != 0)) ||
      (this[0xaf] != 0)) &&
     (((this[0xac] != -0x45245246 || (this[0xad] != -0x41104111)) ||
      ((this[0xae] != -0x153ea5ab || (this[0xaf] != -0x6eeff6ef)))))) {
    iVar1 = _rand();
    // Compare random value against aggression threshold (offset +0x2C0)
    if ((float)iVar1 * DAT_00e44590 <= (float)this[0xb0]) {
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 0;
      uVar2 = FUN_00445f00(this);  // Get current weapon type
      piVar3 = (int *)FUN_00856780(this + 0xac, uVar2, uVar4, uVar5, uVar6);  // Get target entity
      if (piVar3 != (int *)0x0) {
        // Get current position (vtable +0x48)
        (**(code **)(*this + 0x48))(&local_18);
        uStack_10 = 0;
        fStack_c = 0.0;
        fStack_8 = 0.0;
        FUN_008b6b00(&uStack_10);  // Get aim direction
        // Calculate lead position with speed modifier (offset +0x2C4) + global speed offset
        local_18 = local_18 + ((float)this[0xb1] + _DAT_00d5780c) * fStack_c;
        fStack_14 = fStack_14 + ((float)this[0xb1] + _DAT_00d5780c) * fStack_8;
        // Check if weapon has "instant hit" flag (offset +0x290, bit 3)
        if ((*(byte *)(this + 0xa4) & 8) != 0) {
          // Instant hit weapon - use full accuracy
          uVar2 = (**(code **)(*this + 0x58))(1, DAT_00d5ddec, DAT_00d5ddec);
          (**(code **)(iVar1 + 0x170))(&stack0xffffffe4, uVar2);  // Fire weapon at target
          return;
        }
        // Projectile weapon - use spread factor
        uVar2 = (**(code **)(*this + 0x58))(0, 0x3f800000, 0);
        (**(code **)(iVar1 + 0x170))(&stack0xffffffe4, uVar2);  // Fire weapon with spread
      }
    }
  }
  return;
}