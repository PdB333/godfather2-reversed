// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param2, undefined4 param3, char param4, undefined1 param5, undefined4 param6)
{
  undefined4 uVar1;
  float10 fVar2;
  
  this[7] = DAT_00d757dc; // +0x1C
  uVar1 = DAT_00d757d8;   // +0x20
  this[1] = param3;       // +0x04
  this[2] = param2;       // +0x08
  *(undefined1 *)((int)this + 0x31) = param5; // +0x31
  this[8] = uVar1;        // +0x20
  *this = &PTR_FUN_00d757c0; // vtable pointer
  this[3] = 0;            // +0x0C
  this[5] = 0;            // +0x14
  this[6] = 0;            // +0x18
  *(char *)(this + 0xc) = param4; // +0x30 (offset 0x30)
  this[0xd] = param6;     // +0x34
  this[0xb] = 0;          // +0x2C
  this[10] = 0;           // +0x28
  this[9] = 0;            // +0x24
  if (param4 != '\0') {
    fVar2 = (float10)FUN_008f8210(); // Get some time value
    fVar2 = fVar2 * (float10)DAT_00d5f540; // Multiply by a constant
    this[7] = (float)fVar2; // +0x1C
    this[8] = (float)(fVar2 + fVar2); // +0x20
  }
  return this;
}