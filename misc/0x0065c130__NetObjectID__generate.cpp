// FUNC_NAME: NetObjectID::generate
void __thiscall NetObjectID::generate(void)
{
    // Generate a 64‑bit identifier via engine random/fill routine.
    // Parameter 0x40 may be a hint (e.g., size 64) but only first 8 bytes are used.
    uint32 randomLow, randomHigh;
    // Call engine function to fill the 8‑byte buffer starting at &randomLow
    FUN_0064b9e0(0x40, &randomLow);
    m_low = randomLow;   // +0x00
    m_high = randomHigh; // +0x04
}