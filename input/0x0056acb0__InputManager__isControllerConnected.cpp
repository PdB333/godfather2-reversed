// FUNC_NAME: InputManager::isControllerConnected
uint32_t InputManager::isControllerConnected(void)
{
  // in_EAX points to a controller slot index (0-15)
  // Returns 1 if the slot is connected, 0 otherwise
  // The switch covers all valid XInput controller indices
  switch(*in_EAX) {
  default:
    return 0;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x12:
  case 0x14:
  case 0x1a:
    return 1;
  }
}