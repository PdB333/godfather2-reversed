// FUNC_NAME: Player::update
void __fastcall Player::update(Player *this)
{
  int iVar1;
  
  iVar1 = this[0x16]; // +0x58: m_pSimNpc
  this->vtable = &PTR_LAB_00d7702c; // vtable setup
  if (iVar1 != 0) {
    if (((uint)this[0x1c] >> 4 & 1) == 0) { // +0x70: m_flags, check bit 4
      if ((*(uint *)(iVar1 + 0x8e0) >> 4 & 1) != 0) { // SimNpc +0x8e0: some flag
        FUN_008853f0(); // likely updatePlayerActionableTargetSM
      }
      if (((uint)this[0x1c] >> 5 & 1) == 0) { // +0x70: m_flags, check bit 5
        FUN_00886310(); // likely updatePlayerGroundSM
      }
    }
    else {
      if (*(int *)(iVar1 + 0x4a8) != 0) { // SimNpc +0x4a8: m_pVehicle
        FUN_005512c0(0); // likely vehicleUpdate
        if ((*(uint *)(this[0x16] + 0x1b94) >> 0x15 & 1) == 0) { // SimNpc +0x1b94: some flag
          FUN_007f9340(1,1); // likely updateCamera
        }
      }
      iVar1 = FUN_007ff880(); // likely isPlayerInCover
      if (iVar1 != 0) {
        FUN_007ff8a0(0); // likely updateCoverState
      }
    }
    (**(code **)(*(int *)this[0x16] + 0x1b8))(); // SimNpc vtable +0x1b8: update
    FUN_007f6420(0x50); // likely updateInput
    if (((int *)this[0x16] != (int *)0x0) && (((uint)this[0x1c] >> 2 & 1) != 0)) { // +0x70: m_flags, check bit 2
      (**(code **)(*(int *)this[0x16] + 0x7c))(); // SimNpc vtable +0x7c: some update
    }
  }
  if (this[0x14] != 0) { // +0x50: m_pPlayerActionableInfo
    FUN_004daf90(this + 0x14); // likely releasePlayerActionableInfo
  }
  FUN_004ac1e0(); // likely updateAnimation
  return;
}