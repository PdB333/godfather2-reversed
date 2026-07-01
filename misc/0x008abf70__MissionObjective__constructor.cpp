// FUNC_NAME: MissionObjective::constructor
undefined4 * __thiscall MissionObjective__constructor(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();
  }
  FUN_0064d390(0,1);
  *this = &PTR_LAB_00e317dc;  // vtable pointer, base class
  this[6] = 0;                // +0x18: some flag or pointer
  FUN_00454a10(uVar1);
  this[9] = 1;                // +0x24: likely active state = true
  *this = &PTR_LAB_00d79f48;  // vtable pointer, this class
  this[10] = &PTR_FUN_00d79ee0; // +0x28: function pointer, possibly update/execute
  this[0xc] = &LAB_008a8940;  // +0x30: callback or state function
  this[0xd] = 0;              // +0x34: some reference count or state
  this[0xe] = 0;              // +0x38: counter or flag
  this[0xf] = 0;              // +0x3c: another counter
  this[0x10] = 0;             // +0x40: padding or unused
  this[0x11] = 0;             // +0x44: more state
  this[0x12] = 0xffffffff;    // +0x48: index or ID, set to -1 (invalid)
  this[0x13] = 0xffffffff;    // +0x4c: another ID set to -1
  this[0x14] = 0;             // +0x50: some property
  this[5] = this + 10;        // +0x14: pointer to internal buffer at offset 0x28
  return this;
}