// FUNC_NAME: SimObject::setMaterialVariant
void __thiscall SimObject::setMaterialVariant(void *this, undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)((int)this + 0x58);
  uVar2 = FUN_007ab170(param_2);
  FUN_007c4090(uVar1,uVar2);
  return;
}