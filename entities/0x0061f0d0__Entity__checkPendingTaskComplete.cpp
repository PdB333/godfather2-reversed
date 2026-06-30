// FUNC_NAME: Entity::checkPendingTaskComplete
uint Entity::checkPendingTaskComplete(void)
{
    bool bTaskComplete;
    uint uBaseResult; // aggregated from base virtual call

    // +0x98: pointer to a pending task/action object (e.g., animation, behavior)
    if (m_pPendingTask != (int*)0)
    {
        // Check if the task reports completion
        bTaskComplete = IsTaskComplete(); // FUN_00d06180
        if (!bTaskComplete)
        {
            // Task not complete, finalize and notify
            FinalizeTask();             // FUN_00d01870
            NotifyTaskCompletion();     // FUN_00d01890
            TriggerPostTaskAction();    // FUN_00d09ab0
        }
        // Re-check completion status and return inverted (0 if complete, 1 if still active)
        bTaskComplete = IsTaskComplete(); // FUN_00d06180
        return (uint)(bTaskComplete == false);
    }
    // No pending task: propagate base class result, masking lower byte (status flags)
    return uBaseResult & 0xffffff00;
}