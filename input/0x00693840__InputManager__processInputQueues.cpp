// FUNC_NAME: InputManager::processInputQueues
void InputManager::processInputQueues()
{
    char activeSlotByte1; // from global state +0x564
    char activeSlotByte2; // from global state +0x565

    // Global state pointer (likely singleton, e.g. g_inputManager)
    char* pGlobalState = DAT_012233b4;

    activeSlotByte2 = pGlobalState[0x565]; // second active slot indicator
    activeSlotByte1 = pGlobalState[0x564]; // first active slot indicator

    // Process first queue (release queue?)
    if ((activeSlotByte1 != 0x12) && (g_releaseQueueIndex != -1) &&
        (g_releaseQueue[g_releaseQueueIndex] != 0))
    {
        int eventValue = 0;
        int prevIndex = g_releaseQueueIndex;
        // Walk backwards to find the last non-zero entry
        for (; (g_releaseQueueIndex != -1) && (eventValue = g_releaseQueue[g_releaseQueueIndex], eventValue != 0);
             g_releaseQueueIndex--)
        {
            // eventValue updated in condition, loop body empty
        }

        // Get the controller object for the active slot (byte1)
        int* controllerVtable = (int*)FUN_00411070(activeSlotByte1); // returns a __thiscall object pointer
        // Call vtable[2] (offset 8) – likely processEvent or handleEvent
        (**(code**)(*controllerVtable + 8))(eventValue);
    }

    // Process second queue (press queue?)
    if ((activeSlotByte2 != 0x12) && (g_pressQueueIndex != -1) &&
        (g_pressQueue[g_pressQueueIndex] != 0))
    {
        int eventValue = 0;
        int prevIndex = g_pressQueueIndex;
        for (; (g_pressQueueIndex != -1) && (eventValue = g_pressQueue[g_pressQueueIndex], eventValue != 0);
             g_pressQueueIndex--)
        {
            // eventValue updated in condition
        }

        int* controllerVtable = (int*)FUN_00411070(activeSlotByte2);
        (**(code**)(*controllerVtable + 8))(eventValue);
    }
}