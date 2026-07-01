// FUNC_NAME: PlayerF2FSM::setF2FState
void __thiscall PlayerF2FSM::setF2FState(int this, int state, undefined4 param3, undefined4 param4)
{
  // Clear bits 27-28 in flags at +0x11c
  *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) & 0xe7ffffff;
  
  // Store global value at +0x1e8 and +0x1e4 (likely some target/position data)
  *(undefined4 *)(this + 0x1e8) = DAT_00d5ccf8;
  *(undefined4 *)(this + 0x1e4) = DAT_00d5ccf8;
  
  if (state == 1) {
    // State 1: Set bit 27 (0x8000000) - likely "entering F2F" or "start F2F"
    *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) | 0x8000000;
    return;
  }
  
  if (state == 2) {
    // State 2: Store target data and set bit 28 (0x10000000) - likely "in F2F with target"
    *(undefined4 *)(this + 0x1e4) = param3;
    *(undefined4 *)(this + 0x1e8) = param4;
    *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) | 0x10000000;
  }
  
  return;
}