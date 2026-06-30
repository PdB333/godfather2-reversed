// FUNC_NAME: SimManager::createSimObject
// Address: 0x006ab520
// Creates a simulation object with a type flag and extra data.
// param_1: pointer to owner or configuration block
// param_2: byte flag (e.g., active/inactive, type selector)
// param_3: integer parameter (e.g., priority, ID)
uint32_t SimManager::createSimObject(void* param_1, uint8_t param_2, uint32_t param_3)
{
    // Base engine initialization (likely global system setup)
    FUN_005e30c0();

    // Output handle to be filled by the worker function
    uint32_t resultHandle = 0;

    // Temporary 4-byte buffer – may be used to store the flag and padding
    uint8_t tempBuffer[4];
    tempBuffer[0] = param_2;                    // +0x68 from stack base

    // Additional parameters stored on stack (likely passed to the worker via registers or implicit stack)
    uint32_t extraParam = param_3;              // +0x24 from stack base
    uint32_t constantValue = 10;                // +0x18 from stack base

    // Worker function: fills resultHandle and possibly uses tempBuffer & the stack values
    FUN_005e2a80(&resultHandle, param_1, tempBuffer);

    return resultHandle;
}