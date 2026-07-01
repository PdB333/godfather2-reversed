// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass_constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  uVar1 = DAT_00e446f4;
  *this = &PTR_FUN_00d76628;  // vtable pointer
  this[1] = 0;                // +0x04: some pointer/flag
  this[2] = 0;                // +0x08: some pointer/flag
  this[3] = 0;                // +0x0C: some pointer/flag
  this[0xb] = uVar1;          // +0x2C: initialized from global
  this[0xc] = param_2;        // +0x30: constructor parameter
  uVar1 = _DAT_00d5780c;
  this[4] = 0;                // +0x10: some pointer/flag
  this[0xd] = 0;              // +0x34: some pointer/flag
  this[0xe] = uVar1;          // +0x38: initialized from global
  this[0xf] = DAT_00d5eee4;   // +0x3C: initialized from global
  this[0x10] = 4;             // +0x40: some count/flag (initialized to 4)
  this[7] = 0;                // +0x1C: some pointer/flag
  this[6] = 0;                // +0x18: some pointer/flag
  this[5] = 0;                // +0x14: some pointer/flag
  this[10] = 0;               // +0x28: some pointer/flag
  this[9] = 0;                // +0x24: some pointer/flag
  this[8] = 0;                // +0x20: some pointer/flag
  return;
}