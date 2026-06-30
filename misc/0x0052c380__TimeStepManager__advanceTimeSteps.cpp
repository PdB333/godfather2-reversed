// FUNC_NAME: TimeStepManager::advanceTimeSteps
void __thiscall TimeStepManager::advanceTimeSteps(void* this, void* object, float deltaTime)
{
    // Global constants: main step interval and secondary threshold
    extern float kMainStepInterval;   // DAT_00e446f4
    extern float kSecondaryThreshold; // DAT_00e2b05c

    // Repeatedly apply full main steps while deltaTime exceeds the main interval
    while (deltaTime > kMainStepInterval)
    {
        deltaTime -= kMainStepInterval;
        FUN_0052c190(object);  // Perform one main step update on object
    }

    // If remaining deltaTime is greater than the secondary threshold, perform one final step
    if (deltaTime > kSecondaryThreshold)
    {
        FUN_0052c190(object);
    }
}