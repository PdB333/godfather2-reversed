// FUNC_NAME: ControllerInputHandler::updateInputFlags
void __thiscall ControllerInputHandler::updateInputFlags(uint buttonMask, uint unused1, uint unused2, int value)
{
    // +0x14: flags (bitfield for controller button states)
    // +0x28: analog value or timestamp associated with the button flags
    // Global: g_bGlobalXButtonDown (0x0112a7a5) – used for other game systems

    g_bGlobalXButtonDown = (byte)(buttonMask >> 2) & 1;

    uint* flags = (uint*)(this + 0x14);

    // Bit2 (0x4) – X button
    if ((buttonMask & (1 << 2)) == 0)
        *flags &= ~0x4;
    else
        *flags |= 0x4;

    // Bit4 (0x10) – Left Bumper
    if ((buttonMask & (1 << 4)) == 0)
        *flags &= ~0x10;
    else
        *flags |= 0x10;

    // Bit5 (0x20) – Right Bumper
    if ((buttonMask & (1 << 5)) != 0)
        *flags |= 0x20;
    else
        *flags &= ~0x20;

    *(int*)(this + 0x28) = value;  // store associated analog data or time
}