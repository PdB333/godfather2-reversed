// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d7df08;
  this[0xf] = &PTR_LAB_00d7def8;
  this[0x12] = &PTR_LAB_00d7def4;
  this[0x14] = &PTR_LAB_00d7def0;
  this[0x15] = &PTR_LAB_00d7de90;
  this[0x16] = &PTR_LAB_00d7de28;
  // Destroy sub-objects at offsets +0x1B8, +0x1C0, +0x1C8, +0x1D0, +0x1D8
  FUN_004086d0(this + 0x6e);  // likely destructor for some sub-object
  FUN_00408310(this + 0x6e);  // likely cleanup/free
  FUN_004086d0(this + 0x70);
  FUN_00408310(this + 0x70);
  FUN_00408310(this + 0x72);
  FUN_00408310(this + 0x74);
  FUN_00408310(this + 0x76);
  FUN_004df590();  // global cleanup
  // Check flag at +0x1A4 (bit 1)
  if ((*(byte *)(this + 0x69) & 2) != 0) {
    FUN_0081cf20(this);  // release some resource
    this[0x69] = this[0x69] & 0xfffffffd;  // clear bit 1
  }
  iVar1 = this[0x68];  // +0x1A0 pointer
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0;  // null out some field
    this[0x68] = 0;
  }
  FUN_008d8620();  // final cleanup
  return;
}