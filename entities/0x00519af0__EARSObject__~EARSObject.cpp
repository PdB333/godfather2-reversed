// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(undefined4 *this)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = this[0x38]; // +0xE0 - some child object pointer
  *this = &PTR_FUN_00e38238; // vtable for EARSObject
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_009c8f80(); // get allocator
    (**(code **)(*piVar2 + 4))(iVar1,0); // operator delete
  }
  iVar1 = this[0x37]; // +0xDC - another child object pointer
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_009c8f80(); // get allocator
    (**(code **)(*piVar2 + 4))(iVar1,0); // operator delete
  }
  *this = &PTR_LAB_00e381a0; // vtable for base class (likely EARS::Framework::Object)
  return;
}