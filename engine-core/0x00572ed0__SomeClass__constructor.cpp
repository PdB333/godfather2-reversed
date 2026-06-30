// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void)
{
  undefined4 uVar1;
  undefined4 *this; // unaff_ESI
  int *somePointer; // unaff_EDI
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  *this = 0; // +0x00: first member initialized to 0
  this[1] = 0; // +0x04: second member initialized to 0
  uVar1 = FUN_004265d0(&local_c); // call to some initialization function
  this[2] = uVar1; // +0x08: store result
  this[3] = somePointer; // +0x0C: store pointer
  (**(code **)(*somePointer + 8))(); // call virtual function at vtable offset 8
  return;
}