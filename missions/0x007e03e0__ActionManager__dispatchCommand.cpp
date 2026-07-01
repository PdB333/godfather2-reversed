// FUNC_NAME: ActionManager::dispatchCommand
// Address: 0x007e03e0
// Handles dispatching of action commands (0x13, 0x14, 0x15) and delegates others to general handler.
// Returns 0 (false) if action is blocked, 1 (true) if allowed.

uint ActionManager::dispatchCommand(uint slotIndex, uint param3, int commandId, uint param5)
{
    // Command 0x13: specific handler
    if (commandId == 0x13)
    {
        return handleCommand13(slotIndex);
    }

    // Command 0x14: specific handler
    if (commandId == 0x14)
    {
        return handleCommand14(slotIndex);
    }

    // Command 0x15: action availability check
    if (commandId == 0x15)
    {
        // Check if slot index is within valid range (array size at +0x74)
        if (slotIndex < *(uint *)(this + 0x74))
        {
            // First check: player not in free mode? (FUN_004ac870(0))
            if (isPlayerFreeMode(0) == 0)
            {
                return 1; // allowed
            }

            // Second check: player in car and vehicle state is specific
            if (isPlayerInCar(0) != 0)
            {
                int playerVehicle = getPlayerVehicle(); // FUN_007ab1f0()
                if (playerVehicle != 0)
                {
                    int vehicleData = getPlayerVehicle(); // second call (may be same or different)
                    if (*(char *)(vehicleData + 0x1aa) == 0x02)
                    {
                        return 1; // allowed
                    }
                }
            }
        }

        // Global timer vs local cooldown (float at +0x30)
        if (globalTimer < *(float *)(this + 0x30)) // _DAT_00d6f86c
        {
            return 1; // allowed
        }
        return 0; // blocked
    }

    // Unknown command ID: delegate to general handler
    return generalCommandHandler(slotIndex, param3, commandId, param5);
}