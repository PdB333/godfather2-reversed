// FUNC_NAME: AudioManager::constructor
undefined4 * __thiscall AudioManager::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046e6b0(param_2,0x4000);
  *this = &PTR_FUN_00d7e748;
  this[0xf] = &PTR_LAB_00d7e738;   // +0x3C - vtable or function pointer
  this[0x12] = &PTR_LAB_00d7e734;  // +0x48
  this[0x14] = &PTR_LAB_00d7e730;  // +0x50
  this[0x15] = &PTR_LAB_00d7e6d0;  // +0x54
  this[0x16] = &PTR_LAB_00d7e668;  // +0x58
  this[0x60] = 0x19;               // +0x180 - some count (25)
  this[0x61] = 1;                  // +0x184 - boolean flag
  this[0x62] = 0;                  // +0x188
  this[99] = 0;                    // +0x18C
  this[100] = 0;                   // +0x190
  this[0x65] = 0;                  // +0x194
  this[0x66] = 0;                  // +0x198
  this[0x67] = 0;                  // +0x19C
  *(undefined2 *)(this + 0x68) = 0;      // +0x1A0
  *(undefined2 *)((int)this + 0x1a2) = 0; // +0x1A2
  this[0x69] = 0;                  // +0x1A4
  *(undefined2 *)(this + 0x6a) = 0;      // +0x1A8
  *(undefined2 *)((int)this + 0x1aa) = 0; // +0x1AA
  this[0x6b] = 0;                  // +0x1AC
  *(undefined2 *)(this + 0x6c) = 0;      // +0x1B0
  *(undefined2 *)((int)this + 0x1b2) = 0; // +0x1B2
  this[0x6d] = 0;                  // +0x1B4
  *(undefined2 *)(this + 0x6e) = 0;      // +0x1B8
  *(undefined2 *)((int)this + 0x1ba) = 0; // +0x1BA
  this[0x6f] = 0;                  // +0x1BC
  this[0x70] = 0xffffffff;         // +0x1C0 - invalid index
  this[0x71] = 0xffffffff;         // +0x1C4 - invalid index
  this[0x72] = 0;                  // +0x1C8
  *(undefined1 *)(this + 0x73) = 0;      // +0x1CC
  *(undefined1 *)((int)this + 0x1cd) = 0; // +0x1CD
  this[0x76] = 0;                  // +0x1D8
  this[0x75] = 0;                  // +0x1D4
  this[0x74] = 0;                  // +0x1D0
  if (DAT_01206a20 != 0) {
    FUN_00408900(this + 0xf, &DAT_01206a20, 0x8000); // copy string data
  }
  FUN_004089b0(this + 0x6b, "mus_safehouse_award_msg"); // set default music event
  return this;
}