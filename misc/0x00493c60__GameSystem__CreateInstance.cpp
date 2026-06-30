// FUNC_NAME: GameSystem::CreateInstance
void* GameSystem::CreateInstance()
{
    // Initialize subsystem 1 (e.g., input manager, network layer)
    SubSystem1::Initialize();
    
    // Initialize subsystem 2 (e.g., scene manager, audio)
    SubSystem2::Initialize();
    
    // Reset global flags and state variables
    // These are likely part of a larger global structure or separate globals
    // Offsets from g_psystemManager at 0x0120f840:
    // +0x4B0 (0120fcf0): m_globalFlags[0..2]
    g_globalFlags[0] = 0;
    g_globalFlags[1] = 0;
    g_globalFlags[2] = 0;
    // +0x4C0 (0120fd00..0120fd0c): m_otherState[0..3]
    g_otherState[0] = 0;
    g_otherState[1] = 0;
    g_otherState[2] = 0;
    g_otherState[3] = 0;
    
    // Set vtable pointers for core system objects
    // g_pSystemManager (0x0120f840) – pointer to the main system manager instance
    // g_pAudioManager (0x0120fa60) – pointer to the audio manager instance
    g_pSystemManager = reinterpret_cast<void*>(&PTR_LAB_00e34d10);
    g_pAudioManager = reinterpret_cast<void*>(&PTR_LAB_00e34d50);
    
    // Return a handle to the system manager (address of the global pointer)
    return &g_pSystemManager;
}