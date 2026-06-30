// FUNC_NAME: SomeClass::constructor
undefined4 __fastcall SomeClass::constructor(int this)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 result;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // likely allocator or singleton
  result = 0;
  local_c = 2; // probably some alloc flags/type
  local_8 = 0x10; // size or alignment
  local_4 = 0;
  iVar2 = (**(code **)*puVar1)(0x2e0, &local_c); // allocate memory (0x2e0 bytes)
  if (iVar2 != 0) {
    result = FUN_006dd1b0(this); // initialize some sub-object
  }
  FUN_006dce00(this + 0x68); // initialize another sub-object at offset +0x68
  return result;
}