// FUNC_NAME: EARSObject::constructor (or BaseEARSObject::init)
undefined4 * __thiscall EARSObject_constructor(undefined4 *this, undefined4 param_2)

{
  // Call base class constructor with 0x4000 flag
  // FUN_0046e6b0 is likely the base EARS object initializer
  FUN_0046e6b0(param_2,0x4000);
  
  // Set vtable pointer at offset 0x60 (likely vtable for derived class)
  this[0x60] = &PTR_LAB_00d71bdc;
  
  // Set primary vtable at object start (+0x00)
  *this = &PTR_FUN_00d80998;
  
  // Set up function pointers/interface tables for various features
  this[0xf] = &PTR_LAB_00d80988;   // +0x3C - feature/subsystem pointer
  this[0x12] = &PTR_LAB_00d80984;  // +0x48 - feature/subsystem pointer
  this[0x14] = &PTR_LAB_00d80980;  // +0x50 - feature/subsystem pointer
  this[0x15] = &PTR_LAB_00d80920;  // +0x54 - feature/subsystem pointer
  this[0x16] = &PTR_LAB_00d808b8;  // +0x58 - feature/subsystem pointer
  this[0x60] = &PTR_LAB_00d80898;  // +0x180 - secondary vtable/interface
  
  // Initialize state variables to 0
  this[100] = 0;   // +0x190 - some state/counter
  this[99] = 0;    // +0x18C - some state/counter
  this[0x62] = 0;  // +0x188 - state flag
  this[0x61] = 0;  // +0x184 - state flag
  this[0x65] = 0;  // +0x194 - state variable
  this[0x66] = 0;  // +0x198 - state variable
  this[0x67] = 0;  // +0x19C - state variable
  this[0x68] = 0;  // +0x1A0 - state variable
  
  return this;
}