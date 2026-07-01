// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass_destructor(SomeClass* this)
{
  uint counter;
  
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d81624;
  this[0xf] = &PTR_LAB_00d81614;  // +0x3C
  this[0x12] = &PTR_LAB_00d81610; // +0x48
  this[0x14] = &PTR_LAB_00d815f8; // +0x50
  
  // Call base destructor
  FUN_008ff530(this);
  
  // Handle +0xC8 (some kind of state/type)
  if ((this[0x32] != 0) && (this[0x32] != 0x48)) {  // +0xC8
    FUN_00790110(0);
    FUN_00791350(this + 0x14);  // +0x50
  }
  
  // Clean up +0xD4 array of references (count in +0xD4)
  counter = 0;
  if (this[0x35] != 0) {  // +0xD4
    do {
      FUN_004086d0(&DAT_012069c4);
      counter = counter + 1;
    } while (counter < (uint)this[0x35]);
  }
  
  // Clean up various data structures
  FUN_004086d0(&DAT_0120e93c);  // Global data
  FUN_00408310(&DAT_0112fee8);  // Global data
  
  // Clean up +0xA0, +0xA8, +0xB0, +0xB8, +0xC0 (pairs of release+destroy)
  FUN_004086d0(this + 0x28);   // +0xA0
  FUN_00408310(this + 0x28);   // +0xA0
  FUN_004086d0(this + 0x2a);   // +0xA8
  FUN_00408310(this + 0x2a);   // +0xA8
  FUN_004086d0(this + 0x2c);   // +0xB0
  FUN_00408310(this + 0x2c);   // +0xB0
  FUN_004086d0(this + 0x2e);   // +0xB8
  FUN_00408310(this + 0x2e);   // +0xB8
  FUN_004086d0(this + 0x30);   // +0xC0
  FUN_00408310(this + 0x30);   // +0xC0
  
  // Handle streaming/loading state
  if (this[0x36] != 0) {  // +0xD8
    if (DAT_0112a680 != 0) {
      FUN_0094b0e0(this[0x36]);  // Unregister from global manager
    }
    if (this[0x37] == 2) {  // +0xDC - State == 2
      FUN_004086d0(&DAT_012069c4);
      this[0x35] = this[0x35] - 1;  // Decrement counter at +0xD4
    }
  }
  
  // Reset streaming state
  this[0x36] = 0;  // +0xD8
  this[0x37] = 0;  // +0xDC
  this[0x38] = 0;  // +0xE0
  
  // Clean up C8 handle
  if (this[0x32] != 0) {  // +0xC8
    FUN_004daf90(this + 0x32);  // +0xC8 - Destroy handle
  }
  
  FUN_0046c640();
  return;
}