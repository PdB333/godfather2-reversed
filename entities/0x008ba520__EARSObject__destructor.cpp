// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d7b5d8; // vtable pointer
  this[0xf] = &PTR_LAB_00d7b5c8; // +0x3C
  this[0x12] = &PTR_LAB_00d7b5c4; // +0x48
  this[0x14] = &PTR_LAB_00d7b5c0; // +0x50
  this[0x15] = &PTR_LAB_00d7b560; // +0x54
  this[0x16] = &PTR_LAB_00d7b4f8; // +0x58
  this[0x60] = &PTR_LAB_00d7b4e0; // +0x180
  FUN_008f67c0(0xb,this); // release child objects (type 0xB)
  FUN_004086d0(&DAT_01218060); // release resource
  FUN_004086d0(&DAT_0120e93c); // release resource
  FUN_004086d0(&DAT_01206980); // release resource
  FUN_004086d0(&DAT_01206970); // release resource
  if (((uint)this[99] >> 0x13 & 1) != 0) { // check flag at +0x18C bit 19
    FUN_004086d0(&DAT_0112f92c); // release resource
  }
  if (((uint)this[99] >> 0x15 & 1) != 0) { // check flag at +0x18C bit 21
    FUN_004086d0(&DAT_0112f8a8); // release resource
  }
  FUN_004086d0(&DAT_0112a628); // release resource
  FUN_004086d0(&DAT_0112a5c4); // release resource
  FUN_004086d0(&DAT_0112a5e0); // release resource
  if (((uint)this[99] >> 3 & 1) != 0) { // check flag at +0x18C bit 3
    FUN_0081cf20(this); // cleanup additional data
  }
  if ((int *)this[0x6c] != (int *)0x0) { // +0x1B0
    (**(code **)(*(int *)this[0x6c] + 0x10))(1); // call vtable method at offset 0x10
  }
  FUN_004df590(); // release some system resource
  FUN_004df590(); // release some system resource (called twice intentionally)
  if (this[0x9c] != 0) { // +0x270
    (*(code *)this[0x9f])(this[0x9c]); // call function pointer at +0x27C with arg at +0x270
  }
  iVar1 = this[0x7a]; // +0x1E8
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // clear pointer at offset 8
    this[0x7a] = 0; // clear reference
  }
  iVar1 = this[0x75]; // +0x1D4
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // clear pointer at offset 8
    this[0x75] = 0; // clear reference
  }
  FUN_0046ea20(); // final cleanup
  return;
}