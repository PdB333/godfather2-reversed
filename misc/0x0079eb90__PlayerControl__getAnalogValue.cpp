// FUNC_NAME: PlayerControl::getAnalogValue
float __thiscall PlayerControl::getAnalogValue(int param2, int param3)
{
    // +0x249c: bitfield flags (bit 1 = invert/enable axis)
    // +0x2498: axis index or mode byte
    if ((*(uint *)(this + 0x249c) >> 1) & 1)
    {
        // Global input enabled check (likely controller connected or input active)
        if (isInputEnabled())
        {
            // Compute the final analog value using axis index, additional parameters
            return computeAnalogValue((byte)*(undefined1 *)(this + 0x2498), param2, param3);
        }
    }
    return 0.0f; // Return neutral when disabled
}