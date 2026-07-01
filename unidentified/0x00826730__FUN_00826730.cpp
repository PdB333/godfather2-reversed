// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall FUN_00826730(undefined4 *this, undefined4 param_2)

{
  undefined4 *vtablePtr;
  
  vtablePtr = this + 1;
  _DAT_0112db5c = this; // Store this pointer to global
  *vtablePtr = &PTR_LAB_00e30fe0; // Set secondary vtable
  *this = &PTR_FUN_00d73510; // Set primary vtable
  *vtablePtr = &PTR_LAB_00d73500; // Override secondary vtable
  FUN_00463980(0xa8896ed8, vtablePtr, param_2); // Call base class constructor with hash
  return this;
}