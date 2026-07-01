// FUNC_NAME: Entity::getParentEntity
int __fastcall Entity::getParentEntity(int this)
{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(this + 0x68) + 0x134);
  if (iVar1 != 0) {
    return iVar1 + -0x48;
  }
  return 0;
}