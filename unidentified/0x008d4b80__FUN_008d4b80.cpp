// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7d63c;
  // Set additional function pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d7d62c;  // +0x3C
  this[0x12] = &PTR_LAB_00d7d628; // +0x48

  // If there's a child object at +0x64, release it
  if ((undefined4 *)this[0x19] != (undefined4 *)0x0) { // +0x64
    (*(code *)**(undefined4 **)this[0x19])(1); // Release with ref count 1
  }

  // Clean up various sub-objects
  FUN_004086d0(&DAT_0120e93c); // Static object cleanup
  FUN_004086d0(this + 0x14);   // +0x50 sub-object
  FUN_00408310(this + 0x14);   // +0x50 sub-object destructor
  FUN_004086d0(this + 0x16);   // +0x58 sub-object
  FUN_00408310(this + 0x16);   // +0x58 sub-object destructor

  // Delete callback objects if they exist
  if (this[0x21] != 0) { // +0x84
    (*(code *)this[0x24])(this[0x21]); // +0x90 function pointer
  }
  if (this[0x1b] != 0) { // +0x6C
    (*(code *)this[0x1e])(this[0x1b]); // +0x78 function pointer
  }

  // Final cleanup
  FUN_0046c640();
  return;
}