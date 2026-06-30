// FUNC_NAME: InputDevice::handleEvent
// 0x004ff910: Handles input event messages (button press/release/etc) by setting bit flags and optional string conversion.
// The object at param_1 has:
//   +0x28: pointer to some data (maybe a device-specific state) - if non-null, a string conversion is performed.
//   +0x3c: bitfield flags (bit1=press? bit2=release? bit3=other)

void __thiscall InputDevice::handleEvent(InputDevice *this, int eventId)
{
  undefined stackBuf[16]; // buffer for possible event string conversion
    
  if (eventId == 0x26ba025e) { // likely "button down" event hash
    this->flags = (this->flags & 0xfffffffb) | 2; // clear bit2, set bit1
  }
  else {
    if (eventId == 0x79c328b9) { // likely "button up" event hash
      // Clear the stack buffer
      memset(stackBuf, 0, sizeof(stackBuf));
      if (this->pData != (void *)0x0) {
        // If there's associated data, convert event to string? (function at 0x004e94a0)
        // Note: this call uses &stackBuf as an output buffer
        FUN_004e94a0(&stackBuf, 0);
        return;
      }
      // No data: set bit3 (maybe indicates an unhandled release)
      this->flags = this->flags | 8;
      return;
    }
    if (eventId == 0x8a1c9390) { // -0x75e36c70, likely "button hold" event hash
      this->flags = (this->flags & 0xfffffffd) | 4; // clear bit1, set bit2
      return;
    }
  }
  return;
}