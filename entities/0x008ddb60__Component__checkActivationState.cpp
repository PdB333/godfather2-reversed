// FUNC_NAME: Component::checkActivationState
void __fastcall Component::checkActivationState(int component)
{
    char activationAllowed;
    int gameStatePtr;

    // Flags:
    // +0x14 bit0 = disabled flag
    // +0x30 bit4 = pending activation flag
    // +0x30 bit1 = already started flag
    if (((*(byte *)(component + 0x14) & 1) == 0) && ((*(byte *)(component + 0x30) & 4) == 0))
    {
        // Get global game state manager pointer (e.g., SimManager)
        gameStatePtr = **(int **)(DAT_012233a0 + 4);
        activationAllowed = '\0';

        if ((gameStatePtr != 0) && (gameStatePtr != 0x1f30))
        {
            // Read a field at offset -0x48 from the game state (likely a component or mode ID)
            int someObj = *(int *)(gameStatePtr - 0x48);
            if ((someObj != 0) && (someObj = getComponentState(someObj), someObj != 0))
            {
                // Determine if this component/state is allowed to be active
                activationAllowed = canComponentBeActive(someObj);
            }
            // Update the global active status (e.g., for UI/HUD)
            setGlobalActiveFlag(activationAllowed);

            if (activationAllowed == '\x01')
            {
                // If already started, skip activation
                if ((*(byte *)(component + 0x30) & 2) != 0)
                    return;
                // Perform activation (e.g., start state, enable component)
                activateComponent();
                return;
            }
        }
        // Clear the "already started" flag if activation is not allowed
        if ((*(byte *)(component + 0x30) & 2) != 0)
        {
            *(byte *)(component + 0x30) &= 0xfd;
        }
    }
}