// FUNC_NAME: MathUtils::lerpColor
uint MathUtils::lerpColor(int param_1, undefined4 param_2)
{
  uint in_EAX;
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = in_EAX & 0xffffff00;
  if (param_1 != 0) {
    iVar1 = FUN_00471610(); // likely getComponentA
    iVar2 = FUN_00471610(); // likely getComponentB
    uVar3 = FUN_007f7f30(iVar2 + 0x30,iVar1 + 0x30,iVar1 + 0x20,param_2); // lerp between two colors
  }
  return uVar3;
}