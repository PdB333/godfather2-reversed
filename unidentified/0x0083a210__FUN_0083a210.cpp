// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  // Set vtable pointer (likely for base class)
  *this = &PTR_FUN_00d73e98;
  
  // Initialize various member function pointers or data at known offsets
  this[0xf] = &PTR_LAB_00d73e88;   // +0x3C
  this[0x12] = &PTR_LAB_00d73e84;  // +0x48
  this[0x14] = &PTR_LAB_00d73e80;  // +0x50
  this[0x15] = &PTR_LAB_00d73e20;  // +0x54
  this[0x16] = &PTR_LAB_00d73db8;  // +0x58
  this[0x60] = &PTR_LAB_00d73da4;  // +0x180
  
  // Initialize three pairs of objects at offsets +0x290, +0x298, +0x2A0
  // Each pair appears to be a constructor/destructor or init/cleanup pattern
  FUN_004086d0(this + 0xa4);  // +0x290 - likely constructor or init
  FUN_00408310(this + 0xa4);  // +0x290 - likely another init step
  FUN_004086d0(this + 0xa6);  // +0x298
  FUN_00408310(this + 0xa6);  // +0x298
  FUN_004086d0(this + 0xa8);  // +0x2A0
  FUN_00408310(this + 0xa8);  // +0x2A0
  
  // Call some global initialization function
  FUN_008ba520();
  
  return;
}