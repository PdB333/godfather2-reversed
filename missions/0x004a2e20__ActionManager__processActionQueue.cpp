// FUNC_NAME: ActionManager::processActionQueue
void ActionManager::processActionQueue()
{
    // +0x1bc: lastActionIndex (inclusive bound, -1 if none)
    int lastIdx = *(int *)(this + 0x1bc);
    if (lastIdx < 0) {
        return;
    }

    // Array of PendingAction structures starting at this + 0x14C.
    // PendingAction layout (28 bytes each):
    //   +0x00: actionType (int)
    //   +0x04: targetObject (int* / handle) – also used as list node pointer
    //   +0x08: nextAction (int*) – linked list pointer for removal
    //   +0x0C: param1 (int)
    //   +0x10: param2 (int)
    //   +0x14: param3 (int)
    //   +0x18: param4 (int, cast to char for type 2)
    int *actionBase = (int *)(this + 0x150); // points to targetObject of first action (offset +0x04)

    for (int i = 0; i <= lastIdx; i++)
    {
        int *actionField = actionBase; // points to targetObject field

        int actionType = actionField[-1]; // type is one int before

        if (actionType == 1)
        {
            int targetObj = *actionField;
            if (targetObj != 0)
            {
                int value = targetObj - 0x48; // some offset handle
                if (value != 0)
                {
                    // FUN_004a1a10(this, param1, value, param2, param3, 0)
                    executeActionType1(this, actionField[3], value, actionField[2], actionField[4], 0);
                }
            }
        }
        else if (actionType == 2)
        {
            int targetObj = *actionField;
            if (targetObj != 0 && targetObj != 0x48)
            {
                // FUN_004a1c50(param1, param2, param3, (char)param4)
                executeActionType2(actionField[3], actionField[2], actionField[4], (char)actionField[5]);
            }
        }
        else if (actionType == 3)
        {
            // FUN_004a1f50(this, param1)
            executeActionType3(this, actionField[3]);
        }

        // Clear the action type
        actionField[-1] = 0;

        // Remove the action from a linked list of pending actions
        int listNode = *actionField; // targetObject used as node pointer
        if (listNode != 0)
        {
            int *listNext = *(int **)(listNode + 4); // node's next pointer (offset +0x04)
            if (listNext == actionField) // node points back to this action's targetObject field
            {
                *(int *)(listNode + 4) = actionField[1]; // skip this action
            }
            else
            {
                int *prev = (int *)listNext[1]; // walk list
                while (prev != actionField)
                {
                    listNext = (int *)listNext[1];
                    prev = (int *)listNext[1];
                }
                listNext[1] = actionField[1]; // unlink this action
            }
            *actionField = 0; // clear targetObject
        }

        // Clear additional fields
        actionField[2] = 0;
        actionField[3] = 0;

        // Advance to next action (7 ints = 28 bytes)
        actionBase += 7;
    }

    // Mark all actions as processed
    *(int *)(this + 0x1bc) = -1;
}