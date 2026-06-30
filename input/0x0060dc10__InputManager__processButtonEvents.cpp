// FUNC_NAME: InputManager::processButtonEvents
void InputManager::processButtonEvents(void)
{
    int oldState;
    int newState;
    int *pManager;
    uint value;

    for (int slot = 0; slot < 5; slot++)
    {
        oldState = gButtonEvents[slot].oldState; // DAT_011f38f0[slot*2]
        newState = gButtonEvents[slot].newState; // DAT_011f38f4[slot*2]
        gButtonEvents[slot].oldState = 0;
        gButtonEvents[slot].newState = 0;
        pManager = gInputManager; // DAT_01205750

        if (oldState != 0 || newState != 0)
        {
            if (slot == 4)
            {
                // Special slot: call method at vtable+0x9c
                (**(code **)(*gInputManager + 0x9c))(gInputManager, 0);
            }
            else if (slot == 0)
            {
                // Slot 0: get a value from somewhere, then call method at vtable+0x94
                value = FUN_00609260(); // e.g., getCurrentTriggerValue?
                (**(code **)(*pManager + 0x94))(pManager, 0, value);
                gSomeFlag = 1; // DAT_01223538
            }
            else
            {
                // Other slots: call method at vtable+0x94 with slot index and 0
                (**(code **)(*gInputManager + 0x94))(gInputManager, slot, 0);
            }
        }
    }
    return;
}