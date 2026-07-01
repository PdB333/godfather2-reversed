// FUNC_NAME: PlayerCCTVariables::updateGroundCollision
void __fastcall PlayerCCTVariables::updateGroundCollision(PlayerCCTVariables *this)
{
  bool bVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  
  // Call virtual function at vtable+0x198 - likely isOnGround()
  bVar1 = (**(code (__thiscall **)(PlayerCCTVariables *))(*(int *)this + 0x198))(this);
  if (bVar1) {
    // Call virtual function at vtable+0x1b0 - likely getGroundHeight()
    fVar4 = (float10)(**(code (__thiscall **)(PlayerCCTVariables *))(*(int *)this + 0x1b0))(this);
    // Compare against global ground collision threshold
    if ((float10)DAT_00d5ef84 < fVar4) {
      this[0x3ca] = this[0x3ca] & 0xffff7fff; // Clear bit 15 (0x8000) - likely isGrounded flag
      FUN_00861550((float)fVar4); // Resolve collision at this height
    }
    // Check if player is in a certain state (2 = likely dead/downed)
    iVar3 = FUN_00544b70(); // GetPlayerState or similar
    if (iVar3 != 2) {
      FUN_00875690(); // Apply gravity
    }
    // Check and clear falling states
    uVar2 = this[0x3ca];
    if ((uVar2 >> 0x11 & 1) != 0) { // Check bit 17 - isFalling flag
      if ((uVar2 >> 0x12 & 1) == 0) { // Check bit 18 - isJumping flag
        if ((uVar2 >> 0x13 & 1) != 0) { // Check bit 19 - isLanding flag
          this[0x3ca] = this[0x3ca] & 0xfff7ffff; // Clear bit 19
        }
      }
      else {
        this[0x3ca] = this[0x3ca] & 0xfffbffff; // Clear bit 18
      }
    }
    // Check for landing on ground and resolve it
    if ((((this[0x3cb] != 1) && (((uint)this[0x3ca] >> 0xe & 1) == 0)) && // Not in special state, not bit 14
        (0.0 < (float)this[0x28b])) && // Vertical velocity > 0 (falling)
       (fVar5 = (float)this[0x28b] - DAT_012067e8, // Subtract ground collision threshold
        this[0x28b] = (int)fVar5, fVar5 < 0.0)) {
      FUN_0085f410(); // Land on ground - set grounded state
      return;
    }
  }
  return;
}