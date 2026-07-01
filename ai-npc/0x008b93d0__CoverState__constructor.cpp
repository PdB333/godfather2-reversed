// FUNC_NAME: CoverState::constructor
undefined4 * __thiscall CoverState::constructor(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();
  }
  FUN_0064d390(1,1);
  *this = &PTR_LAB_00e317dc;          // vtable setup
  this[6] = 0;                         // +0x18
  FUN_00454a10(uVar1);
  this[9] = 3;                         // +0x24 - initial state
  *this = &PTR_LAB_00d7b4b4;          // vtable update
  this[0xd] = 0;                       // +0x34
  this[10] = &PTR_LAB_00d7b488;       // +0x28
  this[0xc] = &LAB_008b8a40;          // +0x30 - function pointer
  FUN_0084d330();
  this[5] = this + 10;                 // +0x14 = &this[0xa]
  return this;
}