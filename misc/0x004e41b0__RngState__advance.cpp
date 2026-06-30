// FUNC_NAME: RngState::advance
void RngState::advance()
{
    // g_rngIndex and g_rngBuffer[20] are global state for a lagged Fibonacci generator
    // DAT_0119478c -> g_rngIndex (0..19)
    // DAT_01194790 -> g_rngBuffer[20] (int array)

    int newIndex = g_rngIndex - 1;               // previous slot
    int plus3Index = g_rngIndex + 2;             // slot +3 relative to old index

    // Wrap indices modulo 20
    if (newIndex < 0) {
        newIndex = 19;                            // wrap around (0 - 1 -> 19)
    } else if (plus3Index > 19) {
        plus3Index = g_rngIndex - 18;             // equivalent to (g_rngIndex + 2) - 20
    }

    // Update buffer: newIndex slot += slot at +3 offset
    g_rngBuffer[newIndex] += g_rngBuffer[plus3Index];
    g_rngIndex = newIndex;
}