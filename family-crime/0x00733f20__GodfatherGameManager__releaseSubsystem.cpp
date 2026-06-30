// FUNC_NAME: GodfatherGameManager::releaseSubsystem
// Address: 0x00733f20
// This function releases a subsystem if active (indicated by pointer at +0x1f3c),
// then performs a final cleanup on the provided argument.
void __thiscall GodfatherGameManager::releaseSubsystem(void* param2)
{
    // Check if the subsystem is active (non-null pointer at offset 0x1f3c)
    if (*(int*)(this + 0x1f3c) != 0)
    {
        // Release the subsystem embedded at offset 0x203c
        // subsystemRelease is a global function at 0x006f9770 taking (subsystem*, owner)
        subsystemRelease((void*)(this + 0x203c), this);
        // Mark subsystem as inactive
        *(int*)(this + 0x1f3c) = 0;
    }
    // Call cleanup callback on param2 (global function at 0x004d3d90)
    cleanupCallback(param2);
    return;
}