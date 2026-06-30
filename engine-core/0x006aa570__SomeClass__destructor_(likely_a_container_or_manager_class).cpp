// FUNC_NAME: SomeClass::destructor (likely a container or manager class)
void __fastcall SomeClass::~SomeClass(undefined4 *this)
{
  undefined4 *puVar1;
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5d9b8;
  // Set some internal pointer
  this[3] = &PTR_LAB_00d5d9b4;
  
  // Iterate over an array of elements (likely pointers to objects)
  puVar1 = (undefined4 *)this[4]; // +0x10: pointer to array start
  if (puVar1 != puVar1 + this[5]) { // +0x14: element count
    do {
      FUN_006aa160(*puVar1); // Call destructor on each element
      puVar1 = puVar1 + 1;
    } while (puVar1 != (undefined4 *)(this[4] + this[5] * 4));
  }
  
  // Free the array memory
  if (this[4] != 0) {
    FUN_009c8f10(this[4]); // operator delete[] or free
  }
  
  // Reset vtable pointer
  this[3] = &PTR_LAB_00d5d9ac;
  
  // Clear a global flag
  DAT_011299ac = 0;
  
  // Call some cleanup function
  FUN_004083d0();
  
  return;
}