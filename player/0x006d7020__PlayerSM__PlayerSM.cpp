// FUNC_NAME: PlayerSM::PlayerSM
undefined4 * __thiscall PlayerSM::PlayerSM(undefined4 *this, undefined4 param_2)
{
  int *piVar1;
  undefined4 uVar2;

  // Base class initialization: likely SimPlayer or similar
  FUN_006c9760(param_2, _DAT_00d5cf70);

  // Set vtable pointers for this object and a sub-object (maybe second vtable)
  *this = &PTR_FUN_00d5f500;          // main vtable
  this[2] = &PTR_LAB_00d5f4f8;        // secondary vtable (offset +0x08)

  // Initialize two sub-objects (e.g., state machine components)
  FUN_006d69c0();
  FUN_006d69c0();

  // Store global timing/tick value at +0x230 (0x8c * 4)
  uVar2 = DAT_00d5d740;
  this[0x8b] = 0;          // +0x22C
  this[0x8c] = uVar2;      // +0x230: something with timing
  this[0x8d] = 0;          // +0x234

  // Clear state flags (offset in 32-bit units)
  this[0x76] = 0;          // +0x1D8
  *(undefined1 *)(this + 0x8e) = 0; // +0x238 (byte)
  this[0x98] = 0;          // +0x260
  this[0x99] = 0;          // +0x264

  this[0x3e] = 0;          // +0xF8
  this[0x3f] = 0;          // +0xFC
  this[0x40] = 0;          // +0x100
  this[0x41] = 0;          // +0x104
  this[0x42] = 0;          // +0x108

  this[0x4d] = 0;          // +0x134
  this[0x4e] = 0;          // +0x138
  this[0x51] = 0;          // +0x144
  this[0x50] = 0;          // +0x140
  this[0x4f] = 0;          // +0x13C

  this[0x79] = 0;          // +0x1E4
  this[0x78] = 0;          // +0x1E0
  this[0x77] = 0;          // +0x1DC

  this[0x7c] = 0;          // +0x1F0
  this[0x7b] = 0;          // +0x1EC
  this[0x7a] = 0;          // +0x1E8

  this[0x7f] = 0;          // +0x1FC
  this[0x7e] = 0;          // +0x1F8
  this[0x7d] = 0;          // +0x1F4

  piVar1 = this + 0x98;    // Pointer to offset +0x260
  this[0x82] = 0;          // +0x208
  this[0x81] = 0;          // +0x204
  this[0x80] = 0;          // +0x200

  this[0x8f] = 0;          // +0x23C
  this[0x90] = 0;          // +0x240
  this[0x91] = 0;          // +0x244
  *(undefined1 *)(this + 0x92) = 0; // +0x248 (byte)
  this[0x89] = 0;          // +0x224
  this[0x8a] = 0;          // +0x228

  this[0x93] = 0;          // +0x24C
  this[0x94] = 0;          // +0x250
  this[0x96] = 0;          // +0x258
  this[0x97] = 0;          // +0x25C

  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);  // Cleanup if pointer at +0x260 is non-null
    *piVar1 = 0;
  }

  // Clear another block of state flags
  this[0x83] = 0;          // +0x20C
  this[0x84] = 0;          // +0x210
  this[0x85] = 0;          // +0x214
  this[0x86] = 0;          // +0x218
  this[0x87] = 0;          // +0x21C
  this[0x88] = 0;          // +0x220

  return this;
}