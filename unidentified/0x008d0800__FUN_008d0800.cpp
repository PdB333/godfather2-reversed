// FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::~SomeClass(SomeClass *this)
{
  int *piVar1;
  int iVar2;

  // Set vtable pointer to destructor vtable
  this->vtable = &PTR_FUN_00d7ceec;
  // Set function pointers at offsets 0x3C and 0x48
  this->someFuncPtr1 = &PTR_LAB_00d7cedc; // +0x3C
  this->someFuncPtr2 = &PTR_LAB_00d7ced8; // +0x48

  // Check flag at byte offset 0x9E (bit 4)
  if ((*(byte *)((int)this + 0x9E) & 0x10) != 0) {
    // Clear the flag
    *(byte *)((int)this + 0x9E) &= 0xEF;
    // Call some cleanup function with type 0x15
    FUN_008f67c0(0x15, this);
  }

  // Call global reference decrement or mutex release
  FUN_004086d0(&DAT_0120e93c);

  piVar1 = &this->field_0x88; // +0x88 (offset 0x22*4)
  // Check if pointer at +0x88 is non-zero and not 0x48
  if ((this->field_0x88 != 0) && (this->field_0x88 != 0x48)) {
    if (*piVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1 - 0x48;
    }
    // Call some allocation-related function
    FUN_004088c0(iVar2 + 0x3C);
  }

  // Free pointer at +0x90 (offset 0x24*4)
  if (this->field_0x90 != 0) {
    FUN_004daf90(&this->field_0x90);
  }

  // Free pointer at +0x88
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
  }

  // Final cleanup
  FUN_008cfc40();
}