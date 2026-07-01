// FUNC_NAME: AudioDataManager::stopAudioEvent
void __fastcall AudioDataManager::stopAudioEvent(int this)
{
    char lookupResult;
    int someObj; // preserved register (ESI) from caller context, likely a manager instance
    int globalData;
    undefined3*** foundEvent;
    undefined1 stack_30;
    undefined** stack_vtable;
    undefined4 stack_hash;
    int stack_next;
    undefined4 stack_field20;
    undefined4 stack_field1c;
    undefined4 stack_field18;
    undefined4 stack_field14;
    undefined1 stack_field10;
    undefined4 stack_field0c;

    // Check if we have a valid audio entry at this+0x50
    if (*(int **)(this + 0x50) != (int *)0x0)
    {
        // Obtain global data pointer (likely a list manager)
        if (**(int **)(DAT_012233a0 + 4) == 0)
        {
            globalData = 0;
        }
        else
        {
            globalData = **(int **)(DAT_012233a0 + 4) + -0x1f30;
        }

        foundEvent = (undefined3***)0x0;

        // Look up event by hash (0x369ac561 probably a string hash for "stop" or similar)
        lookupResult = (**(code **)(**(int **)(this + 0x50) + 0x10))(0x369ac561, &foundEvent);
        if ((lookupResult != '\0') && (someObj != 0))
        {
            // Initialize temporary node on stack
            stack_field14 = 0;
            stack_field18 = 0;
            stack_field1c = 0;
            stack_vtable = &PTR_FUN_00d5dbbc;   // Node vtable
            stack_next = 0;
            stack_field20 = 0;
            stack_field10 = 0;
            stack_field0c = DAT_01205228;
            stack_hash = 0xc7dc3515;            // Another hash (for removal?)

            // Insert node into a linked list at globalData+0x48 (prev/next fields)
            if ((globalData != 0) && (globalData + 0x48 != 0))
            {
                stack_field20 = *(undefined4 *)(globalData + 0x4c);
                *(int **)(globalData + 0x4c) = &stack_next;
                stack_next = globalData + 0x48;
            }

            foundEvent = &stack_vtable;
            stack_30 = 0;

            // Dispatch the event (function at 0x00408bf0 takes the node and someObj+0x3c)
            FUN_00408bf0(&stack_field0c, someObj + 0x3c, 0);

            // Remove the temporary node from the list
            if (stack_next != 0)
            {
                FUN_004daf90(&stack_next);
            }
        }
    }
    return;
}