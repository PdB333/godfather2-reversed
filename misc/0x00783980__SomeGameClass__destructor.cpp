// FUNC_NAME: SomeGameClass::destructor
void __fastcall SomeGameClass::destructor(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d696e0; // vtable[0] - likely base class vtable
  this[4] = &PTR_LAB_00d696cc; // +0x10 - some pointer/data member
  this[7] = &PTR_LAB_00d696c4; // +0x1C - another pointer/data member
  
  // Clean up various global resources (mutexes, semaphores, etc.)
  FUN_004086d0(&DAT_0120e93c);
  FUN_004086d0(&DAT_0112ad84);
  FUN_004086d0(&DAT_0112b36c);
  FUN_00408310(&DAT_0112af60);
  FUN_004df590();
  
  // Check and delete child object at +0x70
  if (this[0x1c] != 0) {
    FUN_0094b0e0(this[0x1c]); // likely delete or release
    this[0x1c] = 0;
  }
  
  // Check bit 1 of flag at +0x74
  if (((uint)this[0x1d] >> 1 & 1) != 0) {
    FUN_00783460(0); // maybe unregister/callback
  }
  
  // If there's a pointer at +0xC, check and potentially call cleanup
  if (this[3] != 0) {
    iVar1 = FUN_0043b870(DAT_01131018);
    if (iVar1 != 0) {
      FUN_009af0a0(this + 4); // call cleanup on +0x10
    }
  }
  
  FUN_007832f0(); // likely final cleanup step
  
  // Clean up object at +0x40
  if (this[0x10] != 0) {
    FUN_004daf90(this + 0x10);
  }
  
  // Clean up object at +0x3C
  iVar1 = this[0xf];
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // reset some pointer in that object
    this[0xf] = 0;
  }
  
  *this = &PTR_FUN_00d587e0; // switch vtable to base destructor vtable
  FUN_004083d0(); // base class destructor call
  return;
}