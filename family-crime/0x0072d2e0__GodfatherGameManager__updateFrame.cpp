// FUNC_NAME: GodfatherGameManager::updateFrame
void __fastcall GodfatherGameManager::updateFrame(int thisPtr) // __thiscall via ECX
{
    // Base update (possibly simulating physics, animations, or other engine subsystems)
    baseUpdate(); // 0x004df6e0

    // Check if a critical subsystem pointer at +0x2120 is active (e.g., m_pActiveSim, m_pPlayer)
    if (*(int *)(thisPtr + 0x2120) != 0)
    {
        // Perform additional update for that subsystem (e.g., debug rendering, gameplay interception)
        activeSubsystemUpdate(); // 0x0090c610
    }
}