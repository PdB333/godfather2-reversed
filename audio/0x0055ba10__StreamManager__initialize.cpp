// FUNC_NAME: StreamManager::initialize
void StreamManager::initialize(void)
{
    // First stage: basic audio stream subsystem initialization
    InitializeStreamCore();  // FUN_00460c50

    // Second stage: initialize specific stream managers (e.g., BNK, multi-track)
    InitializeStreamManagers();  // FUN_0055ba60

    return;
}