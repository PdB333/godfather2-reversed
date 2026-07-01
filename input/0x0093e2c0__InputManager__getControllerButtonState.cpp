// FUNC_NAME: InputManager::getControllerButtonState
uint __fastcall InputManager::getControllerButtonState(int this)
{
  uint eax;
  uint result;
  
  eax = *(uint *)(DAT_01129c4c + 0x5c); // +0x5c: controller state bitfield
  switch(*(undefined4 *)(this + 8)) { // +0x08: button index
  case 0: // A button
    return (eax >> 0xc) & 0xffffff01;
  case 1: // B button
  case 4: // Left bumper
  case 5: // Right bumper
  case 6: // Back button
    return (eax >> 1) & 0xffffff01;
  case 2: // X button
    return (eax >> 0x17) & 0xffffff01;
  case 3: // Y button
    result = (eax >> 0x14) & 0xffffff01;
  }
  return result;
}