// FUNC_NAME: SubsystemManager::getHandleAndCheckReady
// Function address: 0x00627fa0
// Role: Checks if a subsystem is ready, logs error if not, and optionally returns a handle.
// Called from: 0x0062d1d0 (likely another subsystem initialization)

extern const char* SUBSYSTEM_ERROR_STRING; // +0x00e2a8ac

int SubsystemManager::getHandleAndCheckReady(uint32_t* outHandle)
{
    int isReady = isSubsystemReady(); // FUN_00625a70 - returns 0 if not ready
    if (isReady == 0) {
        logError(SUBSYSTEM_ERROR_STRING); // FUN_00627ac0 - prints/logs error string
    }
    if (outHandle != nullptr) {
        uint32_t handle = getSubsystemHandle(); // FUN_00625ae0 - retrieves subsystem handle
        *outHandle = handle;
    }
    return isReady; // returns readiness status (0 = not ready, non-zero = ready)
}