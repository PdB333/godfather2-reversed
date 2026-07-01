// FUNC_NAME: InputManager::isControllerConnected
uint InputManager::isControllerConnected(void)
{
  char cVar1;
  int *piVar2;
  uint uVar3;
  undefined4 local_4;
  
  piVar2 = (int *)InputManager::getInstance(); // FUN_00946cc0
  if (piVar2 != (int *)0x0) {
    uVar3 = 0x38523fc3; // controller slot index
    local_4 = 0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0x38523fc3,&local_4); // vtable+0x10: isControllerConnected
    return -(uint)(cVar1 != '\0') & uVar3;
  }
  return 0;
}