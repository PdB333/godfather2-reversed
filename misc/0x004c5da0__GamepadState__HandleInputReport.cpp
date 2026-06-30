// FUNC_NAME: GamepadState::HandleInputReport
void GamepadState::HandleInputReport(void)
{
  // This function updates the internal state from a raw input report (32 bytes).
  // If this object is the active controller, it also forwards packed data to the input system.

  // in_EAX points to the incoming input report (4 x 8-byte slots)
  uint64_t* inputReport = in_EAX;

  // Copy the 4 slots into the controller's state at offsets 0xbc, 0xc4, 0xcc, 0xd4
  *(uint64_t*)(this + 0xBC) = inputReport[0];
  *(uint64_t*)(this + 0xC4) = inputReport[1];
  *(uint64_t*)(this + 0xCC) = inputReport[2];
  *(uint64_t*)(this + 0xD4) = inputReport[3];

  // Check if this is the active (local) controller
  if (g_activeController == this)
  {
    // Pack a 16-byte parameter for call #1:
    // First 4 bytes: low word of slot 0 (offset +0xBC)
    // Next 4 bytes: low word of slot 1 (offset +0xC4)
    // Next 4 bytes: high word of slot 0 (offset +0xC0)
    // Last 4 bytes: zero padding
    uint32 param1[4];
    param1[0] = *(uint32*)(this + 0xBC);
    param1[1] = *(uint32*)(this + 0xC4);
    param1[2] = *(uint32*)(this + 0xC0);
    param1[3] = 0;

    // Call #1: e.g., set left analog stick
    InputSystem::SetAnalogInput(*(uint32*)(this + 0x10),  // controller index?
                                *(uint32*)(this + 0xA4),  // input type?
                                param1);

    // Pack a 16-byte parameter for call #2:
    // First 4 bytes: high word of slot 2 (offset +0xD0)
    // Next 4 bytes: low word of slot 3 (offset +0xD4)
    // Next 4 bytes: high word of slot 3 (offset +0xD8)
    // Last 4 bytes: zero padding
    uint32 param2[4];
    param2[0] = *(uint32*)(this + 0xD0);
    param2[1] = *(uint32*)(this + 0xD4);
    param2[2] = *(uint32*)(this + 0xD8);
    param2[3] = 0;

    // Call #2: e.g., set right analog stick
    InputSystem::SetAnalogInput(*(uint32*)(this + 0x10),  // controller index
                                *(uint32*)(this + 0xA8),  // input type
                                param2);
  }
}