// FUNC_NAME: Player::processPendingAction
uint __thiscall Player::processPendingAction(int thisPtr, uint actionData)
{
    // Read 32-bit flags field at offset 0x249c (likely bitmask of pending actions)
    uint pendingFlags = *(uint *)(thisPtr + 0x249c);
    // Check if bit 1 of the flags is set (shift right by 1, then mask LSB)
    uint shiftedFlags = pendingFlags >> 1;
    if ((shiftedFlags & 1) != 0)
    {
        // Global validation/state check (returns bool in low byte)
        uint validationResult = FUN_00481620();
        if ((char)validationResult != '\0')
        {
            // Read action index from byte at offset 0x2498 (maybe an opcode ID)
            byte actionIndex = *(byte *)(thisPtr + 0x2498);
            // Dispatch to specific handler with the action index and provided data
            return FUN_00464b40(actionIndex, actionData);
        }
    }
    // Return the high 24 bits of the shifted flags (mask off low byte)
    return shiftedFlags & 0xffffff00;
}