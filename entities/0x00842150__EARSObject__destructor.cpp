// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  // Clean up if pSomePointer at +0x180 is not null
  if (this[0x60] != 0) {
    FUN_004daf90(this + 0x60); // likely operator delete or cleanup function
  }
  
  // Set vtable pointers if this is a valid object (non-null)
  if (this != (undefined4 *)0x0) {
    this[4] = &PTR_LAB_00d74760; // secondary vtable for derived class interface (+0x10)
    *this = &PTR_LAB_00d74620;   // primary vtable
    return;
  }
  
  // Pure static destructor case? Unusual assignment to global
  ppuRam00000000 = &PTR_LAB_00d74620;
  return;
}