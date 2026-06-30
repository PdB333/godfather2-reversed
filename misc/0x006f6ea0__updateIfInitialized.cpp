// FUNC_NAME: updateIfInitialized
// Address: 0x006f6ea0
// Role: Wrapper that conditionally calls an update routine if a global flag is set.
// Global at 0x0112aa10 likely indicates whether some subsystem (e.g. debug, input, audio) is active.

void updateIfInitialized(void)
{
    // DAT_0112aa10: Global flag (non‑zero if the system is initialized/active)
    if (DAT_0112aa10 != 0) {
        FUN_006f6530(); // Internal update function (e.g., frame update for the subsystem)
        return;
    }
    return;
}