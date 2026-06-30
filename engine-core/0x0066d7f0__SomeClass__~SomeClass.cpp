// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(undefined4 *this)
{
  int iVar1;
  
  iVar1 = this[6];
  *this = &PTR_LAB_00e444a0;
  this[1] = &PTR_LAB_00e444bc;
  if (iVar1 != 0) {
    FUN_00644300();
    FUN_009c8eb0(iVar1);
  }
  FUN_009c8f10(this[3]);
  this[1] = &PTR_LAB_00e362e4;
  this[1] = &PTR_LAB_00e362b8;
  *this = &PTR___purecall_00e30fac;
  return;
}