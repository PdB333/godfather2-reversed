// FUNC_NAME: SimManager::runSimulationSteps

// Function at 0x00581030
// Runs a batch of simulation steps, used for physics/AI tick updates
// param_2 (int) is the number of steps to execute
void SimManager::runSimulationSteps(int stepCount)
{
    // Begin batch: prepare context for multiple simulation steps
    beginUpdateBatch();

    // Execute each step (e.g., per-frame AI update, physics substep)
    for (int i = 0; i < stepCount; i++)
    {
        processSingleStep();
    }

    // Finalize batch: commit changes, notify listeners, etc.
    // Pass 'this' so the finalizer can update manager state
    finalizeUpdateBatch(this);
}