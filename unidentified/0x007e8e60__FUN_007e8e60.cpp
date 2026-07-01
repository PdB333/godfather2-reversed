// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  undefined4 *puVar1;
  char cVar2;
  
  puVar1 = (undefined4 *)((int)this + 0x50); // +0x50: some member
  *(int *)this = (int)&PTR_FUN_00d6fd40; // vtable pointer
  *(int *)((int)this + 0x3c) = (int)&PTR_LAB_00d6fd30; // +0x3c: another vtable or function pointer
  *(int *)((int)this + 0x48) = (int)&PTR_LAB_00d6fd2c; // +0x48: another vtable or function pointer
  cVar2 = FUN_00402080(puVar1); // some initialization check
  if (cVar2 != '\0') {
    FUN_004086d0(puVar1); // sub-object initialization
    FUN_00408310(puVar1); // sub-object initialization
  }
  puVar1 = (undefined4 *)((int)this + 0x58); // +0x58: another member
  cVar2 = FUN_00402080(puVar1); // similar initialization check
  if (cVar2 != '\0') {
    FUN_004086d0(puVar1); // sub-object initialization
    FUN_00408310(puVar1); // sub-object initialization
  }
  FUN_0046c640(); // global initialization or singleton setup
  return;
}