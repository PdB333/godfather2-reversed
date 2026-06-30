// FUNC_NAME: RumbleEffect::update
void __thiscall RumbleEffect::update(void) {
  // +0x10: state (e.g., 0=idle, 1=active, 7=triggerRumble)
  // +0x14: subState (set to 2 after rumble triggered)
  // +0x2c: flags (cleared bits 0x84)
  // +0x100: rumble value (motor speed)

  if (this->state != 1) {
    // state is not active idle -> check for trigger
    if (this->state == 7) {
      // Trigger rumble on default controller
      InputDeviceManager* mgr = InputDeviceManager::getInstance(); // static singleton
      if (mgr) {
        ControllerSlot* slot = mgr->getFirstSlot(); // vtable+4
        if (slot) {
          slot->setRumbleSpeed(this->rumbleValue); // vtable+0x20
        }
      }
    }
    // Reset to idle with subState=2
    this->state = 0;
    this->subState = 2;
  }

  // Clear rumble-active and pending flags
  this->flags &= ~0x84; // clear bits for rumble finished
}