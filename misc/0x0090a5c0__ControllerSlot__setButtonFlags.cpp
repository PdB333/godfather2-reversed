// FUNC_NAME: ControllerSlot::setButtonFlags
void __thiscall ControllerSlot::setButtonFlags(uint buttonMask)
{
  // +0x10: button flags (bitmask of currently pressed buttons)
  buttonFlags |= buttonMask;

  // +0x8: owner ID (0 = unassigned, 0x48 = AI/disabled)
  if (ownerId != 0 && ownerId != 0x48 && 
      isGameActive() && 
      ((InputManager*)g_InputManager)->isReady()) 
  {
    ((InputManager*)g_InputManager)->processButtonEvent(buttonMask);
  }
}