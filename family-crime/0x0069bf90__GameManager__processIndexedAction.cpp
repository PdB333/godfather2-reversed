// FUNC_NAME: GameManager::processIndexedAction
void __thiscall GameManager::processIndexedAction(uint32 this, uint32 actionId)
{
    // Enter profiler / scope marker (called twice: start and within)
    scopeEnter(this);

    // Check if game mode is active or if current entity index is valid
    int isActive = isGameActive(); // FUN_00699ff0
    // g_currentEntityIndex (DAT_00e506ac) must be within [0, count of entities)
    // g_entityListStart (DAT_01129f8c) and g_entityListEnd (DAT_01129f90) define the array
    int entityCount = (g_entityListEnd - g_entityListStart) >> 2;
    if ((isActive != 0) ||
        ((g_currentEntityIndex >= 0) && (g_currentEntityIndex < entityCount)))
    {
        scopeEnter(this); // second scope marker (maybe for inner block)

        // Resolve action callback from actionId
        // The struct holds three args and a function pointer
        struct ActionCallbackInfo {
            int32 arg0;
            int32 arg1;
            int32 arg2;
            void (*callback)(int32);
        } callbackInfo;

        resolveActionCallback(&callbackInfo, actionId); // FUN_0069b4b0

        // If the first argument is non‑zero, call the callback with it
        if (callbackInfo.arg0 != 0)
        {
            callbackInfo.callback(callbackInfo.arg0);
        }
    }
}