// FUNC_NAME: CriticalSection::Initialize
void __thiscall CriticalSection::Initialize(LPCRITICAL_SECTION pCriticalSection)
{
    // Null-check the critical section pointer
    if (pCriticalSection != nullptr) {
        // Clear the debug info pointer (field at +0x04 in CRITICAL_SECTION)
        pCriticalSection->DebugInfo = nullptr;
        // Initialize critical section with a spin count of 10
        InitializeCriticalSectionAndSpinCount(pCriticalSection, 10);
    }
}