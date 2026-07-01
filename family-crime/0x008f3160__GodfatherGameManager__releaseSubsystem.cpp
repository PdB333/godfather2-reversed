// FUNC_NAME: GodfatherGameManager::releaseSubsystem
void __fastcall GodfatherGameManager::releaseSubsystem(int thisPtr)
{
    // +0x2098: pointer to a subsystem interface (e.g., AudioDataManager, StreamManager)
    int* subsystem = *(int**)(thisPtr + 0x2098);
    if (subsystem != nullptr) {
        // Call the second virtual function (vtable+4) on the subsystem.
        // Assumed to be a release/shutdown method; the subsystem object is freed internally.
        (*(void (__thiscall*)(int*))(((int*)*subsystem)[1]))(subsystem);
        // Clear the pointer to prevent double-release.
        *(int**)(thisPtr + 0x2098) = nullptr;
    }
    return;
}