// FUNC_NAME: GodfatherGameManager::resetAndInitializeSubsystems
void __fastcall GodfatherGameManager::resetAndInitializeSubsystems(int thisPtr)
{
    // Clear the initialization flag at offset +0x60 (e.g., m_bSubsystemsReady)
    *(int*)(thisPtr + 0x60) = 0;

    // Initialize the first subsystem (likely audio or input related)
    // The argument 0 might indicate default configuration index
    SubsystemA::initialize(0);

    // Initialize the second subsystem (e.g., streaming or data manager)
    SubsystemB::initialize();
}