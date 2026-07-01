// FUNC_NAME: InputManager::getButtonDown
uint InputManager::getButtonDown(int *this, uint buttonMask)
{
  char isDown;
  uint outMask;

  outMask = 0;
  isDown = (**(code **)(*this + 0x10))(buttonMask, &outMask);
  return -(uint)(isDown != '\0') & buttonMask;
}