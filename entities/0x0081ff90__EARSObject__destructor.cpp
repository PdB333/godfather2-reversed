// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_FUN_00d73364;
  
  // Set additional vtable pointers for derived class interfaces
  this[0xf] = &PTR_LAB_00d73354;  // +0x3C - second vtable pointer
  this[0x12] = &PTR_LAB_00d73350; // +0x48 - third vtable pointer
  
  // If there's a managed object pointer, call its destructor through the vtable
  if (this[0x3a] != 0) {  // +0xE8 - managed object pointer
    (*(code *)this[0x3d])(this[0x3a]);  // +0xF4 - destructor function pointer
  }
  
  // Call base class destructor
  FUN_008339d0();
  
  return;
}