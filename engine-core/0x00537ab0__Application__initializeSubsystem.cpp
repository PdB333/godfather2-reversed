// FUNC_NAME: Application::initializeSubsystem
void Application::initializeSubsystem(void)
{
    // g_pCoreData is global core data pointer
    void* coreData = DAT_0121a390; // global core data
    // g_pApp is global application instance; offset 0x10 is likely m_pSubsystemManager
    void* subsystemManager = *(void**)(DAT_0121b638 + 0x10); // Application +0x10 -> SubsystemManager
    // Register core data with subsystem manager
    FUN_0060ab00(coreData, subsystemManager);
    return;
}