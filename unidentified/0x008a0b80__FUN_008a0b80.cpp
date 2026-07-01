// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d78918;
  this[0xf] = &PTR_LAB_00d78908;
  this[0x12] = &PTR_LAB_00d78904;
  this[0x14] = &PTR_LAB_00d78900;
  this[0x15] = &PTR_LAB_00d788a0;
  this[0x16] = &PTR_LAB_00d78838;
  FUN_0089ff70(this); // likely base class destructor
  if (this[0x79] != 0) {
    FUN_004df600(); // some cleanup function
  }
  FUN_004086d0(&DAT_012069c4); // release global resource
  FUN_004086d0(this + 0x75); // release member at +0x1D4
  FUN_00408310(this + 0x75); // reset member at +0x1D4
  FUN_004086d0(this + 0x77); // release member at +0x1DC
  FUN_00408310(this + 0x77); // reset member at +0x1DC
  FUN_00408310(this + 0x73); // reset member at +0x1CC
  iVar1 = this[0x79];
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // clear pointer at offset +8
    this[0x79] = 0; // clear member at +0x1E4
  }
  FUN_0046ea20(); // final cleanup
  return;
}