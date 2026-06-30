// FUNC_NAME: unknown_class::initializeCooldownTimers
void __thiscall unknown_class::initializeCooldownTimers(uint timer1, uint timer2)
{
    // Store timer values at +0x80 and +0x90
    *(uint *)(this + 0x80) = timer1;    // +0x80: cooldown timer 1
    *(uint *)(this + 0x90) = timer2;    // +0x90: cooldown timer 2

    // Clear active flags for both timers
    *(byte *)(this + 0x84) = 0;         // +0x84: timer1 active flag (bool)
    *(byte *)(this + 0x94) = 0;         // +0x94: timer2 active flag (bool)

    // Clear bit 2 of state flags at +0x4c (likely indicates timer running)
    *(uint *)(this + 0x4c) &= 0xfffffffb;  // +0x4c: state flags (bit 2 = timer active)
}