// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  int iVar1;
  undefined4 uVar2;
  
  FUN_0073e160(param_2, param_3);
  FUN_007ca800();
  this[0x25] = &PTR_FUN_00e32808;  // +0x94: vtable pointer
  this[0x26] = 0;                   // +0x98: some field
  *this = &PTR_LAB_00d67d7c;       // +0x00: vtable pointer
  this[0x1c] = &PTR_LAB_00d67d78;  // +0x70: vtable pointer
  this[0x25] = &PTR_LAB_00d67d74;  // +0x94: vtable pointer (overwritten)
  this[0x27] = 0;                   // +0x9c: some field
  if (this[0x12] == 0) {           // +0x48: check if pointer is null
    iVar1 = 0;
  }
  else {
    iVar1 = this[0x12] + -0x48;    // +0x48: adjust pointer by -0x48
  }
  this[0x28] = iVar1;              // +0xa0: store adjusted pointer
  this[0x29] = 0;                  // +0xa4: some field
  this[0x2a] = 0;                  // +0xa8: some field
  this[0x2b] = 0;                  // +0xac: some field
  this[0x2c] = 0;                  // +0xb0: some field
  this[0x2d] = 0;                  // +0xb4: some field
  FUN_007f63e0(3);                 // some initialization function
  if (this[0x28] != 0) {          // +0xa0: check if adjusted pointer is non-null
    uVar2 = FUN_0043b870(DAT_01131018);  // allocate something
    this[0x2e] = uVar2;           // +0xb8: store allocation result
    return this;
  }
  this[0x2e] = 0;                 // +0xb8: set to null
  return this;
}