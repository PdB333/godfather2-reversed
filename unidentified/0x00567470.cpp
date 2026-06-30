// Function address: 0x00567470
// Likely a state machine initialization for an entity or AI component.
// Sets three fields: state ID (int at +0x10) to 9, substate/flag (byte at +0x14) to 2,
// and a parameter (int at +0x18) from the caller.

void __thiscall SomeClass::setStateWithData(int param1, int param2)
{
    // Offset +0x10: primary state (e.g., kStateActive)
    *(int *)(param1 + 0x10) = 9;
    // Offset +0x14: secondary flag or substate (e.g., kFlagWaiting)
    *(char *)(param1 + 0x14) = 2;
    // Offset +0x18: associated data (e.g., target ID or timer value)
    *(int *)(param1 + 0x18) = param2;
}