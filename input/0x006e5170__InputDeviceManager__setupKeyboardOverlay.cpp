// FUNC_NAME: InputDeviceManager::setupKeyboardOverlay
void InputDeviceManager::setupKeyboardOverlay(undefined4 *this)

{
  undefined4 *keyboardOverlay;
  undefined4 overlayId;
  
  keyboardOverlay = (undefined4 *)((int)this + 0x100); // +0x100: keyboard overlay object
  overlayId = 0x55859efa; // 0x55859efa - keyboard overlay ID/hash
  this = (undefined4 *)0x0;
  (**(code **)(*(int *)*keyboardOverlay + 0x10))(0x55859efa,&this); // getOverlay(id) or createOverlay
  *this = overlayId; // store overlay ID
  return;
}