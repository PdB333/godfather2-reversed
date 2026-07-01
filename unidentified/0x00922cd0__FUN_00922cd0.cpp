// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(undefined4 param_1)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate 0xF0 bytes
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // initialize base class
  }
  FUN_00981eb0(param_1); // base class constructor call
  *(undefined4 *)(iVar1 + 0x20) = 0xda139445; // set vtable or magic number at +0x20
  *(undefined4 *)(iVar1 + 0xc) = 7; // set some field at +0x0C to 7
  FUN_00982400(1); // initialize something with parameter 1
  *(code **)(iVar1 + 0x14) = FUN_00982b30; // set function pointer at +0x14
  FUN_00982e10(); // finalize initialization
  return;
}