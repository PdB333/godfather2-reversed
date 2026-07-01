// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  uVar1 = FUN_00ab3c50(*this);  // Call base class constructor or initialization function
  *this = uVar1;  // Assign the result to the object's vtable pointer or first field
  return this;
}