// FUNC_NAME: InputManager::processControllerEvent
// Address: 0x008ad8f0
// Handles a controller input event, creating an event object and pushing it to the event queue.
// Also performs fallback handling if allocation fails, and processes callbacks from the current menu/substate.

void __thiscall InputManager::processControllerEvent(InputManager* this, int eventId)
{
    int* piVar1;
    char cVar2;
    int iVar3;
    int iVar4;
    int* piVar5;
    int uVar6;
    int aiStack_10[3];
    int pcStack_4; // likely a callback pointer from a previous call

    // Global singleton manager pointer (e.g., InputDeviceManager or GameManager)
    int* pManager = (int*)g_pInputManager; // DAT_01223484

    if (*(int*)(pManager + 0x3) != 0) {          // +0x0c: check if input system is initialized
        iVar3 = isGameActive();                   // FUN_00481610
        if (iVar3 != 0) {
            isGameActive();                       // second call possibly to get a handle
            if (g_bControllerMenuActive != 0) {   // DAT_01205a20
                cVar2 = isControllerConnected();   // FUN_00481620
                if (cVar2 != '\0') {
                    iVar4 = allocateEventObject(0x40); // FUN_009c8e50 (new of size 64)
                    if (iVar4 != 0) {
                        iVar4 = createEventObject(this); // FUN_008aa600 (initialize)
                        *(int*)(iVar4 + 0x38) = eventId; // store event ID at +0x38
                        pushEventToQueue(iVar4);          // FUN_0064ef60
                        return;
                    }
                    // Allocation failed – use static fallback
                    g_staticEventId = eventId; // _DAT_00000038
                    pushEventToQueue(0);       // push null event
                    return;
                }
            }
        }

        // Process if a substate manager is active
        if ((**(int**)(this + 0x38)) != 0) {       // +0xe0: pointer to current substate or menu
            // Access substate object
            int* substate = (int*)(**(int**)(this + 0x38) + -0x48); // +0xe0 -> vtable? subtract 0x48 for base
            if (substate != (int*)0x0) {
                // Get current focused object from the manager
                int* pFocused = (int*)(**(int**)(*(int*)(pManager + 0x3) + 2))(); // +0xc -> pointer, vtable offset 8 (index 2) then vtable offset 0xc
                int focusedId = convertToLocalId(pFocused); // FUN_008a8a30
                int processed = processFocusedId(focusedId); // FUN_004d3bc0
                // Call substate's update method with a callback structure
                (**(code**)(*substate + 0x76))(aiStack_10); // vtable offset 0x1d8 (0x76 *4)
                if (aiStack_10[0] != 0) {
                    // Execute callback if provided (pcStack_4 might be a stored function pointer)
                    ((void(*)(int))pcStack_4)(aiStack_10[0]);
                }
                // Clean up the event ID
                releaseEventId(eventId);      // FUN_007f8790
                resetSubstate(substate);       // FUN_008ad820
            }
        }
        // Notify observers/cleanup
        notifySystem(0); // FUN_008ab630
    }
}