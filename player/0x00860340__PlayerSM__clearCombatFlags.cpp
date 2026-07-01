// FUNC_NAME: PlayerSM::clearCombatFlags
void __fastcall PlayerSM::clearCombatFlags(int this)
{
  // Clear combat-related flags at offset +0xF28
  // Mask: 0xFFC3FFFF preserves bits 17-18 (0x3 << 17) and clears others
  // This likely clears specific combat state flags like aiming, shooting, etc.
  *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xffc3ffff;
  return;
}