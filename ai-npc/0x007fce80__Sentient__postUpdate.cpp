// FUNC_NAME: Sentient::postUpdate
void __thiscall Sentient::postUpdate(Sentient *this)
{
  Sentient *targetObj;
  float timerValue;

  // Check if there's a linked object at offset 0xffc (field_ooxffc)
  // The offset 0x3ff in int* terms = 0xffc bytes
  Sentient *pLinkedObj = (Sentient *)this->field_ooxffc;
  if (pLinkedObj != (Sentient *)0x0 && (uint)pLinkedObj != 0x48) {
    // The linked object pointer is stored with a base offset; subtract 0x48 to get actual object
    targetObj = (Sentient *)((char *)pLinkedObj - 0x48);
    if (targetObj != (Sentient *)0x0) {
      // Call virtual function at vtable index 0x198 on the linked target
      (targetObj->vtable[0x198])(targetObj);
    }
  }

  // Call a base class update function (likely shared update logic)
  FUN_007fc9f0();

  // Call own virtual function at vtable index 0x198
  (this->vtable[0x198])(this);

  // Process bit flag 5 (0x20) in the state flags at offset 0x970 (field_oox970)
  if ((this->field_oox970 & 0x20) != 0) {
    // Virtual function at 0xc0 returns a timer value (e.g., remaining time for an effect)
    timerValue = ((float (__thiscall *)(Sentient *))this->vtable[0x30])(); // offset 0xc0 = 192 bytes = index 0x30
    if (timerValue > 0.0f) {
      // Clear the flag and call a state transition function
      this->field_oox970 &= ~0x20;
      FUN_007f7050();
    }
  }

  // Process bit flag 6 (0x40) similarly
  if ((this->field_oox970 & 0x40) != 0) {
    timerValue = ((float (__thiscall *)(Sentient *))this->vtable[0x30])();
    if (timerValue > 0.0f) {
      this->field_oox970 &= ~0x40;
      FUN_007f7050();
      return;
    }
  }
}