// FUNC_NAME: Player::clearRagdollFlag
void __fastcall Player::clearRagdollFlag(int this)
{
  // Check bit 21 (0x200000) of flags at +0xF28
  if ((*(uint *)(this + 0xf28) >> 0x15 & 1) != 0) {
    // If ragdoll flag was set, call the ragdoll cleanup function
    FUN_008621d0();
  }
  // Clear bits 20-21 (0x300000) of the flags
  *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xffcfffff;
}