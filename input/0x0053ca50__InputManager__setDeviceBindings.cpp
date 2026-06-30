// FUNC_NAME: InputManager::setDeviceBindings
// Function address: 0x0053ca50
// Handles two input device assignments to internal manager slots (offset +0x14 and +0x18)
void __thiscall InputManager::setDeviceBindings(uint param_1, uint param_2)
{
    // Global singleton pointer to the InputManager instance (0x121be7c)
    InputManager* pManager = *(InputManager**)0x0121be7c;

    // Check if first slot's handler object exists (offset +0x14)
    void* firstHandler = *(void**)((int)pManager + 0x14);
    if (firstHandler != 0)
    {
        // Assign device binding for first handler using global UI manager (0x121bc24)
        UIManager::setHandlerDevice(*(void**)0x0121bc24, firstHandler, param_1);
    }

    // Check if second slot's handler object exists (offset +0x18)
    void* secondHandler = *(void**)((int)pManager + 0x18);
    if (secondHandler != 0)
    {
        // Assign device binding for second handler
        UIManager::setHandlerDevice(*(void**)0x0121bc24, secondHandler, param_2);
    }
}