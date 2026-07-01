// FUNC_NAME: PlayerActionableInfo::resetActionableInfo
void __fastcall PlayerActionableInfo::resetActionableInfo(int this)
{
  // Clear flags in hi-bits of actionable state (preserve lower nibble? +0x81c)
  *(uint *)(this + 0x81c) = *(uint *)(this + 0x81c) & 0xfffffff0;
  // Set default actionable state flags: 0x14 = 00010100 binary (e.g., interactable, combat? +0x81c)
  *(uint *)(this + 0x81c) = *(uint *)(this + 0x81c) | 0x14;
  // Set the pointer/reference to the global actionable entity (null or singleton? +0x79c)
  *(undefined4 *)(this + 0x79c) = DAT_00d5ccf8;
  return;
}