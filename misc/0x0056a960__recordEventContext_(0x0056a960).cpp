// FUNC_NAME: recordEventContext (0x0056a960)
// Stores three parameters into global debug log context variables and increments a counter.
// Likely used for tracking recent game events (e.g., for debugging or playback).

void __cdecl recordEventContext(uint32_t param1, uint32_t param2, uint32_t param3)
{
    // +0x0? global counter of times context was set
    gEventContextCounter++;          // _DAT_01205548
    // +0x4? stored parameters (probably last event data)
    gEventContextValue1 = param1;   // DAT_0120554c
    gEventContextValue2 = param2;   // DAT_01205550
    gEventContextValue3 = param3;   // _DAT_01205554 (overlapping symbol)
}