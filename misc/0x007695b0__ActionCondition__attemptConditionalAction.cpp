// FUNC_NAME: ActionCondition::attemptConditionalAction
// This function attempts to perform a two-step action on an owned behavior object.
// Returns 1 if both condition checks and the final action succeed, 0 otherwise.
bool __fastcall ActionCondition::attemptConditionalAction(void* this) {
    // Dereference owner object at offset 0x5c to get a behavior/action interface
    int* behaviorObj = *(int**)((char*)this + 0x5c);
    int actionParam;
    int temp = *(int*)((char*)behaviorObj + 0x24c4); // Load an action ID or state from the behavior
    if (temp == 0) {
        actionParam = 0;
    } else {
        actionParam = temp - 0x48; // Convert to an index or offset (0x48 = 72)
    }

    // Retrieve global state (e.g., game manager)
    void* globalState = (void*)FUN_00471610();
    // Check a flag at offset 0x30 of the global state (e.g., is game running?)
    bool canProceed = (bool)FUN_00718d40((char*)globalState + 0x30);
    if (canProceed) {
        // Virtual call at vtable+0x314: first condition check, takes no extra params
        bool firstCheck = ((bool(*)(void*))(*(void***)behaviorObj)[0x314 / 4])(behaviorObj);
        if (firstCheck) {
            // Virtual call at vtable+0x310: second action, takes actionParam as argument
            bool secondCheck = ((bool(*)(void*, int))(*(void***)behaviorObj)[0x310 / 4])(behaviorObj, actionParam);
            if (secondCheck) {
                return true;
            }
        }
    }
    return false;
}