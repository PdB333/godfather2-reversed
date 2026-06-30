// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  // Set vtable pointer to first virtual function table
  *this = &PTR_FUN_00d5da74; // vtable entry 0
  // Set second vtable pointer (likely for multiple inheritance or interface)
  this[1] = &PTR_LAB_00d5da64; // vtable entry 1

  // Call some initialization function with a global data reference
  FUN_004086d0(&DAT_012069c4); // Initialize some global state

  // Call another initialization function
  FUN_004083d0(); // Additional setup

  // Update vtable pointer to final vtable (after construction complete)
  *this = &PTR_LAB_00d5da60; // Final vtable

  // Set global flag to 0
  DAT_01129900 = 0; // Some initialization complete flag

  return;
}