// FUNC_NAME: EARSObject::validateAndInitialize
int EARSObject::validateAndInitialize(EARSObject* this) {
    if (this == nullptr) {
        return 0;
    }
    // Reset engine subsystems (e.g., audio, input) with zero flags
    CoreEngine::reset(gCoreEngine, 0, 0); // FUN_00462880
    // Yield to allow pending asynchronous processing
    CoreEngine::yield(); // FUN_005708f0
    return 1;
}