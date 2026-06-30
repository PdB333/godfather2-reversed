// FUNC_NAME: SubsystemManager::setMode
void SubsystemManager::setMode(int mode)
{
    char isRunning;

    if (mode == 2) {
        isRunning = isGameRunning();
        if ((isRunning == '\0') && (s_subsystemHandle == '\0')) {
            s_subsystemHandle = createSubsystem();
            return;
        }
    }
    else if ((mode == 0) || (mode == 1)) {
        isRunning = isGameRunning();
        if ((isRunning == '\0') && (s_subsystemHandle != '\0')) {
            destroySubsystem();
            s_subsystemHandle = '\0';
        }
    }
    return;
}