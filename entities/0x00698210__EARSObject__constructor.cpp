// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  uVar1 = EARSObject::vtableInit(*this);
  *this = uVar1;
  return this;
}