// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(void *this)
{
  undefined4 *vtablePtr;
  undefined4 result;
  undefined4 *thisPtr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Set vtable pointer
  *(undefined4 **)this = &PTR_FUN_00e36f74;
  
  // Initialize member variables at offsets +0x14, +0x18, +0x10
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  
  // Set value at +0x04 to 0x19 (25)
  *(undefined4 *)((int)this + 0x04) = 0x19;
  
  // Set value at +0x08 to 0
  *(undefined4 *)((int)this + 0x08) = 0;
  
  // Call some function to get a pointer
  vtablePtr = (undefined4 *)FUN_009c8f80();
  
  // Prepare parameters for a virtual function call
  local_c = 2;
  local_8 = 4;
  local_4 = 0;
  
  // Call virtual function at index 0 of vtable with parameter 100 and pointer to local_c
  result = (**(code **)*vtablePtr)(100, &local_c);
  
  // Store result at +0x0C
  *(undefined4 *)((int)this + 0x0C) = result;
  
  // Set value at +0x44 to 0
  *(undefined4 *)((int)this + 0x44) = 0;
  
  return;
}