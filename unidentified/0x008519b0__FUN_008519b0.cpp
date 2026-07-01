// FUNC_NAME: SomeClass::setColorOrVector4
void __thiscall SomeClass::setColorOrVector4(int thisPtr, undefined4 *param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  uVar3 = param_2[3];
  *(undefined4 *)(thisPtr + 0x30) = *param_2;
  *(undefined4 *)(thisPtr + 0x34) = uVar1;
  *(undefined4 *)(thisPtr + 0x38) = uVar2;
  *(undefined4 *)(thisPtr + 0x3c) = uVar3;
  return;
}