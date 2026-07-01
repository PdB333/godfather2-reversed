// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte param_2)

{
  // Set vtable pointer (base class)
  *this = &PTR_FUN_00d83240;
  
  // Initialize member pointers at offsets +0x3C (0xF * 4) and +0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d83230;  // +0x3C: some function pointer or interface
  this[0x12] = &PTR_LAB_00d8322c; // +0x48: another function pointer or interface
  
  // Initialize sub-object at offset +0x50 (0x14 * 4)
  FUN_004086d0(this + 0x14);  // sub-object constructor
  FUN_00408310(this + 0x14);  // sub-object initialization
  
  // Global initialization call
  FUN_0046c640();
  
  // If param_2 bit 0 is set, allocate and delete? (placement delete pattern)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x74);  // operator delete with size 0x74 (116 bytes)
  }
  
  return this;
}