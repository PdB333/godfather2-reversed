// FUNC_NAME: handleCommand
// Function at 0x0044e6d0: Dispatches commands based on hash (param1) and type (param5).
// Returns 1 on success.
int handleCommand(int commandHash, uint32_t* commandData, int param3, int param4, int commandType)
{
    uint32_t localData[4]; // Copy of command data for certain types
    char unknownFlag;

    if (commandType == 0)
    {
        // Initialize command processor
        FUN_0044d840();

        // Copy 16 bytes from commandData into local struct
        localData[0] = commandData[0];
        localData[1] = commandData[1];
        localData[2] = commandData[2];
        localData[3] = commandData[3];

        // Process command data with param4
        FUN_0044df10(localData, param4);

        // Set default flag if not set
        if (unknownFlag == 0)
        {
            unknownFlag = 2;
        }

        // Dispatch based on command hash
        if (commandHash == 0x580e3e39)
        {
            FUN_0044ee30(localData);
            return 1;
        }
        if (commandHash == 0x774eb208)
        {
            FUN_0044e3e0(localData);
            FUN_0044ef00(DAT_012233a4);
            return 1;
        }
    }
    else if (commandType == 5)
    {
        // Type 5: Validate command data and trigger something
        if (FUN_004508e0(commandData[0], commandData[1], commandData[2], commandData[3]) != 0)
        {
            FUN_004aa7b0(param4);
            return 1;
        }
    }
    else if (commandType == 2)
    {
        // Type 2: Validate and run action
        if (FUN_0044ede0(commandData) != 0)
        {
            FUN_004aa750();
            return 1;
        }
    }
    else if (commandType == 3)
    {
        // Type 3: Validate and run different action
        if (FUN_0044ede0(commandData) != 0)
        {
            FUN_004aa950();
            return 1;
        }
    }
    else if (commandType == 4)
    {
        // Type 4: Validate and run another action
        if (FUN_0044ede0(commandData) != 0)
        {
            FUN_004aa970();
        }
    }

    return 1; // Default success
}