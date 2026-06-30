// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer (likely to a base class or cleanup vtable)
  *this = &PTR_FUN_00d5d980;
  
  // Set additional vtable-like entries at offsets +0x3C, +0x48, +0x50
  // These are likely function pointers for cleanup or virtual dispatch
  this[0xf] = &PTR_LAB_00d5d970;  // +0x3C
  this[0x12] = &PTR_LAB_00d5d96c; // +0x48
  this[0x14] = &PTR_LAB_00d5d968; // +0x50
  
  // Check if a sub-object at offset +0x140 exists and destroy it
  if (this[0x50] != 0) { // +0x140
    FUN_004daf90(this + 0x50); // Destroy sub-object at +0x140
  }
  
  // Call a global cleanup or finalization function
  FUN_00474090();
}