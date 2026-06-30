// FUNC_NAME: GlobalUpdateManager::processFrame
void __cdecl processFrame(void)
{
    // Local variable used as a temporary context buffer (passed to getUpdateContext)
    int tempContext;

    // Obtain the current update context from the engine (likely a pointer to a state/data structure)
    int updateContext = getUpdateContext(&tempContext);

    // Process the update context (e.g., apply input, update simulation)
    processUpdateContext(updateContext);

    // Finalize the frame update (e.g., swap buffers, flush commands)
    finalizeUpdate();
}