// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  undefined4 *allocatedMemory;
  
  *this = &PTR_FUN_00d73400; // vtable pointer
  this[1] = 0; // some member initialized to 0
  allocatedMemory = (undefined4 *)FUN_009c8e80(0x40); // allocate 0x40 bytes (likely operator new or malloc)
  this[2] = allocatedMemory; // store allocated memory pointer
  this[3] = 0; // another member initialized to 0
  this[4] = 0x10; // set some size/capacity to 0x10 (16)
  return this;
}