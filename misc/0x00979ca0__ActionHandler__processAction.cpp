// FUNC_NAME: ActionHandler::processAction
// Function address: 0x00979ca0
// Role: Maps an action ID to a command type and dispatches it with associated data.
// The object has fields:
//   +0x38: pointer/handle to some data (e.g., a string or hash) used to retrieve command details
//   +0xc4: action ID integer (1,2,5,9) mapped to command type (1,3,4,2) respectively; other values yield 0.

// External functions (based on callee analysis):
// FUN_00990db0: Retrieves command data into a 48-byte buffer given a data handle.
extern bool retrieveCommandData(uint dataHandle, char *outBuffer);
// FUN_00979130: Dispatches a command using a 28-byte buffer and a command type byte.
extern void dispatchCommand(char *commandBuffer, byte commandType);

void ActionHandler::processAction()
{
    char cmdDataBuffer[48];   // Buffer for retrieved command data (48 bytes)
    char commandBuffer[28];   // Buffer for final command (28 bytes)
    byte mappedType;

    // Retrieve command data using the object's data handle at +0x38
    if (retrieveCommandData(*(uint*)(this + 0x38), cmdDataBuffer))
    {
        int actionId = *(int*)(this + 0xC4);

        // Map action ID to command type
        if (actionId == 1)
            mappedType = 1;
        else if (actionId == 2)
            mappedType = 3;
        else if (actionId == 5)
            mappedType = 4;
        else
            // For actionId 9: (0 - 1) & 2 = 2; for others: (1 - 1) & 2 = 0
            mappedType = (byte)((actionId != 9) - 1U) & 2;

        // Dispatch the command with the mapped type and the command buffer
        dispatchCommand(commandBuffer, mappedType);
    }
    // No else: if retrieval fails, nothing is dispatched.
}