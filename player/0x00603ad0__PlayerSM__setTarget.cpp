// FUNC_NAME: PlayerSM::setTarget
void __thiscall PlayerSM::setTarget(int thisPtr, undefined4 target, undefined4 param_3)
{
  // +0x80: target entity pointer
  *(undefined4 *)(thisPtr + 0x80) = target;
  // +0x90: some target-related parameter (e.g., target position or sub-target)
  *(undefined4 *)(thisPtr + 0x90) = param_3;
  // +0x84: flag byte for target state (cleared)
  *(undefined1 *)(thisPtr + 0x84) = 0;
  // +0x94: another flag byte (cleared)
  *(undefined1 *)(thisPtr + 0x94) = 0;
  // +0x4c: bitfield flags - clear bit 2 (0x4) to indicate target is set
  *(uint *)(thisPtr + 0x4c) = *(uint *)(thisPtr + 0x4c) & 0xfffffffb;
  return;
}