// FUNC_NAME: PlayerActionableTargetSM::copyFrom
undefined4 * __thiscall PlayerActionableTargetSM::copyFrom(undefined4 *this, int source)
{
  // Call initialization/preparation function on source
  FUN_0081f9f0(source);

  // Set vtable pointer
  *this = &PTR_LAB_00d7366c;

  // Copy 8-byte blocks from source+0x60..0x78 to this+0x60..0x78 (4 blocks = 32 bytes)
  // Likely contains Vector2 or quaternion data
  *(undefined8 *)(this + 0x18) = *(undefined8 *)(source + 0x60);  // +0x60
  *(undefined8 *)(this + 0x1a) = *(undefined8 *)(source + 0x68);  // +0x68
  *(undefined8 *)(this + 0x1c) = *(undefined8 *)(source + 0x70);  // +0x70
  *(undefined8 *)(this + 0x1e) = *(undefined8 *)(source + 0x78);  // +0x78

  // Copy 5 ints from source+0x4c..0x5c to this+0x4c..0x5c
  this[0x13] = *(undefined4 *)(source + 0x4c);  // +0x4c
  this[0x14] = *(undefined4 *)(source + 0x50);  // +0x50
  this[0x15] = *(undefined4 *)(source + 0x54);  // +0x54
  this[0x16] = *(undefined4 *)(source + 0x58);  // +0x58
  this[0x17] = *(undefined4 *)(source + 0x5c);  // +0x5c

  return this;
}