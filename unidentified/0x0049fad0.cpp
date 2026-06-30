// FUN_0049fad0: InputManager::dispatchInputToActiveControllers(uint32_t inputData)
void InputManager::dispatchInputToActiveControllers(uint32_t inputData)
{
    // Check if the manager's input dispatch is enabled (bit 1 at +0xAC)
    if (!(*(byte *)(this + 0xAC) & 2))
        return;

    // Retrieve the array of controller pointers (start at +0x8C) and its count (at +0x90)
    uint32_t count = *(uint32_t *)(this + 0x90);
    Controller **ppController = *(Controller ***)(this + 0x8C);
    Controller **ppEnd = ppController + count;

    // Iterate over all controllers
    while (ppController != ppEnd)
    {
        Controller *controller = *ppController;
        // Check if this controller is active (bit 0 at +0xB2)
        if (controller && (*(byte *)(controller + 0xB2) & 1))
        {
            // Forward input data to the global input handler
            // DAT_012233A8 is a global singleton; +4 likely points to an internal handler or window
            FUN_0042E6E0(*(uint32_t *)(DAT_012233A8 + 4), inputData);
        }
        ppController++;
    }
}