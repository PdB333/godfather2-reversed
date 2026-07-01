// FUNC_NAME: DonControlManager::updateDonMessageDisplay
// Address: 0x008a01a0
// Role: Checks if the player is near a CSA don message trigger (based on spatial hash) and shows/hides the interaction prompt.
// This function iterates a doubly linked list of trigger objects (at this+0x1c), checks a computed hash from player position/rotation against each trigger's stored hash,
// and displays a "Press INTERACT to hide/show don message" prompt. Uses global singletons for UI and input state.

int * __thiscall DonControlManager::updateDonMessageDisplay(int this, int param_2)
{
    // Player coordinate components from param_2 (likely position/rotation)
    int coord0 = *(int *)(param_2 + 0x20); // +0x20 x? or hash component
    int coord1 = *(int *)(param_2 + 0x24); // +0x24 y?
    int coord2 = *(int *)(param_2 + 0x28); // +0x28 z?
    int coord3 = *(int *)(param_2 + 0x2c); // +0x2c rotation? or w?

    // Compute a 4D hash: (((coord0*33 + coord1)*33 + coord2)*33 + coord3)
    int playerHash = ((coord0 * 33 + coord1) * 33 + coord2) * 33 + coord3;

    // Linked list of trigger nodes (head at this+0x1c)
    CSADonTriggerNode* triggerNode = *(CSADonTriggerNode**)(this + 0x1c);
    CSADonTriggerNode* listHead = (CSADonTriggerNode*)(this + 0x1c); // sentinel head
    CSADonTrigger* matchedTrigger = 0; // local_38

    // Iterate over the linked list
    while (triggerNode != listHead) {
        int typeField = triggerNode->type; // offset +0x8
        if (typeField == 0 || typeField == 0x48) {
            // Empty or special node – remove it from list
            CSADonTriggerNode* prev = triggerNode->prev; // offset +0x4
            CSADonTriggerNode* next = triggerNode->next; // offset +0x0
            // Unlink node
            prev->next = next;
            next->prev = prev;
            if (triggerNode->data != 0) {
                FUN_004daf90(&triggerNode->data); // free object
            }
            FUN_009c8f10(triggerNode); // free node
            triggerNode = next;
        } else {
            // The type field points to an associated object at typeField - 0x48
            CSADonTrigger* obj;
            if (typeField == 0) {
                obj = 0;
            } else {
                obj = (CSADonTrigger*)(typeField - 0x48);
            }
            // Check if object's stored hash matches player hash
            if (obj->hash == playerHash && (*(bool (__thiscall**)(CSADonTrigger*))(obj->vtable + 0x158))(obj)) {
                // Matched: call virtual to get label string, float
                char* labelText;
                float timeout;
                (*(void (__thiscall**)(CSADonTrigger*, char**))(obj->vtable + 0x14c))(obj, &labelText);
                float fVal = (*(float (__thiscall**)(CSADonTrigger*))(obj->vtable + 0x150))(obj);
                FUN_004262f0(0); // some initialization
                // Build a temporary vector/point structure for comparison
                // (local_20, uStack_1c, uStack_18, fStack_24)
                struct Vec4 { char* ptr; int a, b; float c; } vec4;
                vec4.ptr = labelText;
                vec4.a = uStack_1c; // from decompiled: uStack_1c, uStack_18 are within local_20 struct
                vec4.b = uStack_18;
                vec4.c = fVal; // float from virtual
                int result = FUN_004bdae0(&vec4);
                if (result == 2) {
                    // Break if comparison yields 2 (success?)
                    matchedTrigger = obj;
                    break;
                }
            }
            triggerNode = triggerNode->next; // move to next node
        }
    }

    // Now decide whether to show/hide the "don message" prompt
    if (matchedTrigger == 0 || *(int*)(DAT_0112a838 + 0x5c) != 0) {
        // Either no match, or a global flag prevents showing
        if (*(char*)(this + 0xd2) != 0) {
            // Hide the message if currently showing
            FUN_005a04a0("HideCSADonMessage", 0, &DAT_00d77dc0, 0);
            *(char*)(this + 0xd2) = 0;
        }
    } else {
        // Show prompt if not already visible
        if (*(char*)(this + 0xd2) == 0) {
            char* triggerLabel = 0;
            // Build label string using trigger's name (at obj+0x1ec? offset 0x7b*4)
            FUN_004d4a60(&triggerLabel, 1, &PTR_LAB_00d78708, matchedTrigger->nameId); // offset 0x1ec?
            char* finalLabel = (triggerLabel != 0) ? triggerLabel : &DAT_0120546e; // fallback?
            // Show prompt: "Press INTERACT" message with label
            FUN_005a04a0("ShowCSADonMessage", 0, &DAT_00d77dc0, 2, finalLabel, "[b=INTERACT]");
            *(char*)(this + 0xd2) = 1;
            if (triggerLabel != 0) {
                // Release string if allocated
                (*pcStack_14)(triggerLabel); // free function pointer on stack
            }
        }
        // Additional check: if player is in a certain state (interacting?), possibly block
        int** globalPtr = *(int***)(DAT_012233a0 + 4);
        if (globalPtr != 0 && *globalPtr != (int*)0x1f30) {
            void* playerState = (*(code**)&(*globalPtr)->vtable)[2](); // virtual call
            int playerInfo = FUN_00410540(playerState);
            if (playerInfo != 0) {
                // If player is in an interaction and not already doing something, return matchedTrigger
                if (((*(byte*)(playerInfo + 0x10) & 0x10) != 0) && ((*(byte*)(playerInfo + 0x12) & 0x10) == 0)) {
                    return matchedTrigger;
                }
                return 0;
            }
        }
    }
    return 0;
}