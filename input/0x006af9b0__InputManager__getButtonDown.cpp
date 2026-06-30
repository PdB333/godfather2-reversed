// FUNC_NAME: InputManager::getButtonDown
uint InputManager::getButtonDown(int *this, uint buttonMask)
{
  char cVar1;
  undefined4 local_4;
  
  local_4 = 0;
  cVar1 = (**(code **)(*this + 0x10))(buttonMask, &local_4);
  return -(uint)(cVar1 != '\0') & buttonMask;
}