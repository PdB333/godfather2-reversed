// FUNC_NAME: ActionCallbackManager::registerCallbacks
void __thiscall ActionCallbackManager::registerCallbacks(void* context)  // param_1 = this, param_2 = context (e.g., ActionMapManager*)
{
    ActionMapManager* actionMapManager;
    char isEnabled;
    int actionIndex;
    Action* action;
    CallbackState* state;
    short actionId;

    // Get ActionMapManager from context (e.g., Player::getActionMapManager)
    actionMapManager = (ActionMapManager*)FUN_00849cf0(context);
    if (actionMapManager != nullptr) {
        // Register default actions stored in the manager
        if (actionMapManager->numActions != 0) {  // +0x98
            for (actionIndex = 0; actionIndex < actionMapManager->numActions; actionIndex++) {
                action = actionMapManager->actions[actionIndex];  // +0x94 is array of Action*
                isEnabled = FUN_006b4440();  // Global input enabled check (e.g., !menuActive)
                if (isEnabled && (FUN_00991300(action->id) != 0)) {  // +0x38 likely action ID/name
                    // Determine callback state pointer
                    if (this == 0) {
                        state = nullptr;
                    } else {
                        state = (CallbackState*)((char*)this + 4);
                    }
                    actionId = action->actionId;  // +0x44
                    // Register default action handler
                    FUN_005c0d50(state, FUN_00990800, (int)actionId);
                }
            }
        }

        // Clear any previously registered custom callbacks
        for (CustomCallbackNode* node = this->customCallbacks; node != nullptr; node = node->next) {
            FUN_005c0d30();  // Probably clears/unregisters callback at node
        }

        // Register custom callbacks from linked list
        CustomCallbackNode* node = this->customCallbacks;
        if (node != nullptr) {
            do {
                FUN_005c0d50(this->state, FUN_009910b0, (int)node->actionId);  // +0x44 actionId
                node = node->next;
            } while (node != nullptr);
        }

        // Clear again (maybe to remove duplicates after registration)
        for (CustomCallbackNode* node = this->customCallbacks; node != nullptr; node = node->next) {
            FUN_005c0d30();
        }

        // Register additional fixed callbacks
        state = (CallbackState*)((char*)this + 4);
        FUN_005c0d50(state, FUN_00990ca0, 0);          // Start sequence
        for (CustomCallbackNode* node = this->customCallbacks; node != nullptr; node = node->next) {
            FUN_005c0d50(state, FUN_00991940, (int)node->actionId);  // Custom action handler
        }
        FUN_005c0d50(state, FUN_00990cc0, 0);          // End sequence
        FUN_005c0d50(state, FUN_00990850, 0);          // Global handler
    }
}