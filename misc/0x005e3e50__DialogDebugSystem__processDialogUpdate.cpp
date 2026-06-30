// FUNC_NAME: DialogDebugSystem::processDialogUpdate
void __cdecl DialogDebugSystem::processDialogUpdate(int entityId) {
    int callbackArg;          // Uninitialized in decompiled code; likely set by previous stack usage
    void (*callbackFunc)(int); // Uninitialized; placeholder for a callback that may be called

    // Push debug scope
    Debug::pushScope("DIALOG");

    // Update dialog manager for the given entity
    gDialogManager->update(entityId);

    // If a callback is pending, invoke it
    if (callbackArg != 0) {
        (*callbackFunc)(callbackArg);
    }

    // Push end of scope (or another scope)
    Debug::pushScope("DIALOG_END");

    // Update again (possibly for the second phase)
    gDialogManager->update(entityId);

    // Invoke callback again if present
    if (callbackArg != 0) {
        (*callbackFunc)(callbackArg);
    }
}