// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(undefined4 param_1)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate 0xF0 bytes (240 bytes) for object
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(FUN_00982b30); // call base class constructor or init function
  }
  FUN_00981eb0(param_1); // initialize some member with param_1
  *(undefined4 *)(iVar1 + 0xc) = 3; // set field at +0x0C to 3 (likely type/state)
  *(undefined4 *)(iVar1 + 0x20) = 0x510c352b; // set field at +0x20 to a magic constant (hash/ID)
  FUN_00982e10(); // finalize initialization
  return;
}