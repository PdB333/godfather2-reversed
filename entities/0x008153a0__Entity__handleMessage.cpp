// FUNC_NAME: Entity::handleMessage
// Address: 0x008153a0
// Role: Processes incoming messages/events for an Entity object.
// Checks message type against global constants and updates internal state.
// Handles two message types: one that increments a counter and possibly dequeues an action,
// and another that looks up and executes actions from a resource.

void __thiscall Entity::handleMessage(int* messageType)
{
    char cVar1;
    int local_4;

    // Check if message type matches first global constant (e.g., kMsgTypeUpdate)
    if (*messageType == DAT_012069c4) {
        // Condition: either resource pointer at +0x1c or +0x20 is non-null,
        // and bit 1 of flags at +0x10 is clear.
        if (((*(int*)(this + 0x1c) != 0) || (*(int*)(this + 0x20) != 0)) &&
            ((*(uint*)(this + 0x10) >> 1 & 1) == 0)) {
            // Increment counter at +0x18 by global increment value
            *(int*)(this + 0x18) = *(int*)(this + 0x18) + DAT_01206804;
        }
        // If action queue pointer at +0x94 is non-null, try to dequeue an action
        if (*(int*)(this + 0x94) != 0) {
            local_4 = 0;
            // FUN_006039d0 likely dequeues an action from the queue; returns action ID in local_4
            FUN_006039d0(*(int*)(this + 0x94), &local_4, &messageType);
            if (local_4 != 0) {
                // Clear queue pointer and delete the dequeued action
                *(int*)(this + 0x94) = 0;
                FUN_00815160(local_4);
                return;
            }
        }
    }
    // Check if message type matches second global constant (e.g., kMsgTypeAction)
    else if (*messageType == DAT_01206978) {
        // Condition: either resource pointer at +0x1c or +0x20 is non-null,
        // and bit 2 of flags at +0x10 is clear.
        if (((*(int*)(this + 0x1c) != 0) || (*(int*)(this + 0x20) != 0)) &&
            ((*(uint*)(this + 0x10) >> 2 & 1) == 0)) {
            local_4 = 0;
            messageType = (int*)0x0; // Reset output pointer for action lookup
            // If resource at +0x1c exists, look up an action using counter at +0x18
            if (*(int*)(this + 0x1c) != 0) {
                cVar1 = FUN_008162b0(*(int*)(this + 0x18), &local_4, &messageType);
                if (cVar1 != '\0') {
                    // Execute the found action
                    FUN_00816370(local_4, messageType);
                }
            }
            // If resource at +0x20 exists, do the same lookup
            if (*(int*)(this + 0x20) != 0) {
                cVar1 = FUN_008162b0(*(int*)(this + 0x18), &local_4, &messageType);
                if (cVar1 != '\0') {
                    FUN_00816370(local_4, messageType);
                }
            }
        }
    }
    return;
}