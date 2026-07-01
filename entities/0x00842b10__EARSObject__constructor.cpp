// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  // Set virtual base table pointer (likely for first base)
  *this = (undefined4 *)&PTR_LAB_00d74620;
  
  // Call base class constructor (likely EARSObject or similar)
  FUN_00598db0();  // rename to EARSObject::baseConstructor(this) or similar
  
  // Set secondary vtable pointer (possibly for second base)
  this[1] = (undefined4 *)&PTR_LAB_00d74968;
  
  // Final vtable override (this is common in MSVC virtual inheritance chains)
  *this = (undefined4 *)&PTR_FUN_00d74964;
  
  // Return constructed object
  return this;
}