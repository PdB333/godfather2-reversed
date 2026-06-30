// FUNC_NAME: ControllerSlot::enableRumble
// Address: 0x006a8980
// Enables vibration for a connected controller by setting the low bit at offset 0x21 of its device-specific data
void __thiscall ControllerSlot::enableRumble(int *this)
{
    // +0x00: connected flag (non-zero means controller is present)
    // +0x08: pointer to device-specific structure (if non-null)
    //   -> +0x21: flags byte (bit 0 = vibration enabled)
    if (this[0] != 0 && this[2] != 0) {
        byte *flags = (byte *)(this[2] + 0x21);
        *flags = *flags | 1;
    }
}