// FUNC_NAME: resetNetworkGlobals
// Function at 0x006185d0 – Resets network-related global variables and calls internal reset routine.
// Called from initialization at 0x006060a0.
// Seems to copy a base value (DAT_01205750) into another global (DAT_0120595c),
// then clears two adjacent 32-bit fields (likely a sequence number pair),
// and finally invokes FUN_00609bf0 (maybe resetting packet buffers or connection state).

void resetNetworkGlobals(void)
{
    // Copy base network value (e.g., initial sequence number or threshold)
    DAT_0120595c = DAT_01205750;
    
    // Clear two consecutive 32-bit fields – likely a slot or ack window reset
    _DAT_011f7440 = 0;
    _DAT_011f7448 = 0;
    
    // Call internal network state reset (e.g., flush reliable packets, reset timers)
    sub_609bf0();
    return;
}