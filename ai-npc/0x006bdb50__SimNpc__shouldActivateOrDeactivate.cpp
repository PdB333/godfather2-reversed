// FUNC_NAME: SimNpc::shouldActivateOrDeactivate
undefined4 __fastcall SimNpc::shouldActivateOrDeactivate(int this)
{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  // Check if either the activation or deactivation flag is set (bit 0 of byte at +0x54 and +0x56)
  if (((*(byte *)(this + 0x54) & 1) == 0) || ((*(byte *)(this + 0x56) & 1) == 0)) {
    // If the NPC is not currently active (slot at +0xd0 is 0), return 1 (should activate)
    if (*(int *)(this + 0xd0) == 0) {
      return 1;
    }
    // Check distance from player (global _DAT_00d577a0 is likely player position or some threshold)
    if ((_DAT_00d577a0 < *(float *)(this + 0x58)) &&
       (pfVar1 = (float *)FUN_00790cd0(), // Get player position
       fVar2 = *pfVar1 - *(float *)(this + 0xc0), // dx
       fVar3 = pfVar1[1] - *(float *)(this + 0xc4), // dy
       fVar4 = pfVar1[2] - *(float *)(this + 200), // dz (offset 0xc8)
       *(float *)(this + 0x58) <= fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2)) {
      // If distance squared is within activation range, deactivate the NPC
      FUN_006bd750(); // SimNpc::deactivate
      return 1;
    }
  }
  return 0;
}