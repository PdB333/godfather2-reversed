// FUNC_NAME: SomeClass::constructor
undefined4* __thiscall SomeClass::constructor(undefined4* this, byte heapAllocatedFlag)
{
  // Set primary vtable pointer at offset 0x00
  *this = &PTR_FUN_00d7ea28;
  // Set secondary vtable pointers for multiple inheritance
  // Offset 0x3C (15*4)
  this[0xf] = &PTR_LAB_00d7ea18;
  // Offset 0x48 (18*4)
  this[0x12] = &PTR_LAB_00d7ea14;
  // Offset 0x50 (20*4)
  this[0x14] = &PTR_LAB_00d7ea10;
  // Offset 0x54 (21*4)
  this[0x15] = &PTR_LAB_00d7e9b0;
  // Offset 0x58 (22*4)
  this[0x16] = &PTR_LAB_00d7e948;
  // Call base class constructor at offset 0x190 (100*4)
  FUN_00408310(this + 100);
  // Global initialization function
  FUN_008d8620();
  // If object was heap-allocated, perform cleanup/deallocation? (likely a custom delete)
  if ((heapAllocatedFlag & 1) != 0) {
    FUN_0043b960(this, 0x1a0);
  }
  return this;
}