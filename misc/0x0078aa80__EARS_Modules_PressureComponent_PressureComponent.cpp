// Xbox PDB: EARS_Modules_PressureComponent_PressureComponent
// FUNC_NAME: PressureComponent::constructor
undefined4 * __thiscall PressureComponent::constructor(undefined4 *this, undefined4 param_2)
{
  this[3] = param_2; // +0x0C: some initialization parameter
  this[1] = 0x21;    // +0x04: size or type field (33)
  this[2] = 0;       // +0x08: counter/state
  this[5] = 0;       // +0x14: unknown
  this[4] = &PTR_LAB_00d58278; // +0x10: vtable or function pointer
  *this = &PTR_FUN_00d69a0c;   // +0x00: vtable pointer
  this[4] = &PTR_FUN_00d699f8; // +0x10: override vtable entry
  this[7] = 0;       // +0x1C: unknown
  this[8] = 0;       // +0x20: unknown
  this[9] = 0xbadbadba;  // +0x24: sentinel/magic value
  this[10] = 0xbeefbeef; // +0x28: sentinel/magic value
  this[0xb] = 0xeac15a55; // +0x2C: sentinel/magic value
  this[0xc] = 0x91100911; // +0x30: sentinel/magic value
  *(undefined2 *)(this + 0xe) = 0; // +0x38: short field zeroed
  *(undefined2 *)((int)this + 0x3a) = 0; // +0x3A: another short field zeroed
  this[0xf] = 0;    // +0x3C: unknown
  this[0x10] = 0;   // +0x40: unknown
  this[0x11] = 0;   // +0x44: unknown
  this[0x12] = 0;   // +0x48: unknown
  this[0x13] = 0;   // +0x4C: unknown
  this[0x14] = 0;   // +0x50: unknown
  this[0x15] = 0;   // +0x54: unknown
  this[0x16] = DAT_00d5e288; // +0x58: copy from global data
  this[0x17] = 0;   // +0x5C: unknown
  this[0xd] = 0;    // +0x34: reset sentinel
  this[0xc] = 0;    // +0x30: reset sentinel
  this[0xb] = 0;    // +0x2C: reset sentinel
  this[10] = 0;     // +0x28: reset sentinel
  this[9] = 0;      // +0x24: reset sentinel
  FUN_00408240(&DAT_0112afc8,"iMsgPressureNearSubmissionZone"); // register message string
  FUN_00408240(&DAT_0112afc0,"iMsgPressureInSubmissionZone");   // register message string
  FUN_00408240(&DAT_0112afd0,"iMsgPressureAboveSubmissionZone"); // register message string
  FUN_00408240(&DAT_0112afe0,"Stimulus_HearPressure_MsgData*"); // register message string
  if (DAT_012069f4 != 0) {
    FUN_00408900(this,&DAT_012069f4,0x8000); // allocate or initialize with size 0x8000
  }
  FUN_00408240(&DAT_0112afd8,"iMsgApplyPlayerInViewPressure"); // register message string
  FUN_004086b0(&DAT_0120e93c,0x7fff); // set some limit or threshold
  this[0x10] = 0;   // +0x40: re-zero after potential allocation
  return this;
}