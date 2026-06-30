// FUNC_NAME: InputManager::processInputChanges
void InputManager::processInputChanges()
{
    // g_inputChanges: array of 5 pairs of ints (presumably per-player or per-controller slot changes)
    static int g_inputChanges[5][2]; // base at DAT_011f38f0 (first int of each pair) and DAT_011f38f4 (second int)
    static InputManager* g_pInputManager = (InputManager*)DAT_01205750; // global singleton
    static bool g_bInputActive = false; // DAT_01223538 flag

    for (int slot = 0; slot < 5; slot++)
    {
        int changeType = g_inputChanges[slot][0];
        int changeParam = g_inputChanges[slot][1];
        g_inputChanges[slot][0] = 0;
        g_inputChanges[slot][1] = 0;

        if (changeType != 0 || changeParam != 0)
        {
            if (slot == 4)
            {
                // Reset/clear for last slot
                // vtable+0x9c is likely "clearInputChange" or "resetSlot"
                (*(void (**)(InputManager*, int))(*(int*)g_pInputManager + 0x9c))(g_pInputManager, 0);
            }
            else if (slot == 0)
            {
                // Slot 0 uses a special getter (FUN_00609260) to retrieve current state
                int currentState = FUN_00609260(); // getter for slot 0 current value
                // vtable+0x94 is likely "updateInputMapping" or "processSlotChange"
                (*(void (**)(InputManager*, int, int))(*(int*)g_pInputManager + 0x94))(g_pInputManager, 0, currentState);
                g_bInputActive = true;
            }
            else
            {
                // Other slots: pass slot index and zero param
                (*(void (**)(InputManager*, int, int))(*(int*)g_pInputManager + 0x94))(g_pInputManager, slot, 0);
            }
        }
    }
}