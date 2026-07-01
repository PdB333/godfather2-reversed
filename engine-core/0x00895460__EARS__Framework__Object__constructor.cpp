// FUNC_NAME: EARS::Framework::Object::constructor
undefined4 * __thiscall EARSObject_constructor(undefined4 *this, byte param_2)

{
  // Set vtable pointer
  *this = &PTR_FUN_00d778f4;
  // Initialize member fields at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d778e4;  // +0x3C
  this[0x12] = &PTR_LAB_00d778e0; // +0x48
  
  // Call base class constructor via vtable
  (*(code *)PTR_FUN_00d7791c)();
  
  // Initialize three mutex/critical section objects
  FUN_00408310(&DAT_0112e31c);  // Initialize critical section 1
  FUN_00408310(&DAT_0112e314);  // Initialize critical section 2
  FUN_00408310(&DAT_01218048);  // Initialize critical section 3
  
  // Call some initialization function
  FUN_0046c640();
  
  // If param_2 bit 0 is set, allocate memory for this object
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 100);  // Allocate 100 bytes? Or operator new?
  }
  
  return this;
}