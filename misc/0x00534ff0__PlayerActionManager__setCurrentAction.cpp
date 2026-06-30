// FUNC_NAME: PlayerActionManager::setCurrentAction

void PlayerActionManager::setCurrentAction(int actionId, void* actionContext)
{
    // Store the desired action and context globally
    gDesiredActionId = actionId;          // _DAT_01219b28
    gDesiredActionContext = actionContext; // _DAT_01219b24

    // Only process if the game is in the main gameplay state
    if (gGameState == &gInGameState)      // DAT_012058e8 == &DAT_01219a70
    {
        // Do not change state while already in either of two special action states (3 or 4)
        if (gCurrentActionState != 3 && gCurrentActionState != 4) // DAT_01219b14
        {
            int newState = 0;
            if (actionContext != nullptr)
            {
                // If we have a context, state becomes 1 (no action) or 2 (has action)
                newState = (actionId != 0) + 1;
            }
            // newState: 0 => no context, 1 => context with idle action, 2 => context with active action

            // Only transition if the state actually changes
            if (gCurrentActionState != newState)
            {
                changeActionState(gCurrentActionState); // FUN_00534d70
            }
        }

        // Access per-player data structure (array of 0x3c-byte entries, indexed by player slot)
        PlayerActionData* playerData = &gPlayerActionData[gPlayerSlot]; // base DAT_01219d3c, index DAT_01219b21

        // If any action-linked (UI/prompt) resources are active, clean them up
        if (playerData->actionPromptHandle1 != 0) // *(int *)(&DAT_01219d3c + slot*0x3c)
        {
            releaseActionPrompt(); // FUN_006063b0
        }
        if (playerData->actionPromptHandle2 != 0) // *(int *)(&DAT_01219d40 + slot*0x3c)
        {
            releaseActionPrompt(); // FUN_006063b0
        }
    }
}