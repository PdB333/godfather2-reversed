// FUNC_NAME: SomeObject::isActive
bool __thiscall isActive(int *this)
{
  int iVar1;
  
  // Call virtual function at vtable offset 0x1fc (0x7f * 4) to check some state
  iVar1 = (**(code (__thiscall **)(int *))(*(int *)this + 0x1fc))(this);
  return iVar1 != 0;
}