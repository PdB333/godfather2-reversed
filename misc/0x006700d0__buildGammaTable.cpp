// FUNC_NAME: buildGammaTable
// Address: 0x006700d0
// Role: Initializes a 128-byte gamma/contrast lookup table for a color effect.
// The table is built by scaling a linear ramp, clamping to a maximum, then multiplying by a factor.
// Entries beyond 0x6f (111) are forced to 0xFF (full brightness).

// Global data references:
// DAT_00e2dd1c -> gammaStep (float) - step size for linear ramp
// DAT_00e2b1a4 -> gammaMax (float) - upper clamp value
// DAT_00e445d0 -> gammaMultiply (float) - scale factor (likely 255.0 to convert to byte)
// DAT_01205178 -> gammaTable (byte[128]) - output table

// FUN_00b9af10 -> probably a thread yield or scheduler hint (no-op in this context)

void buildGammaTable(void)
{
    byte index;          // bVar1 - loop counter (0-127)
    int i;               // iVar2 - linear index
    double dVal;
    float fVal;

    index = 0;
    i = 0;
    do {
        dVal = (double)((float)i * gammaStep);
        // Yield to other threads (no-op in single-threaded context)
        FUN_00b9af10();   // 0x00b9af10 - likely yield or heartbeat
        fVal = (float)dVal;
        if (gammaMax < (float)dVal) {
            fVal = gammaMax;
        }
        gammaTable[i] = (char)(int)(fVal * gammaMultiply);
        if (0x6f < index) {
            gammaTable[i] = 0xff;
        }
        index = index + 1;
        i = i + 1;
    } while (index < 0x80);
    return;
}