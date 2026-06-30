// FUNC_NAME: CriticalSection::initSpinLock
// Address: 0x00643e90
// Role: Initializes a critical section with a spin count of 10.
// The DebugInfo field is cleared before initialization (standard pattern).
void CriticalSection::initSpinLock()
{
    // Ensure the critical section pointer (this) is valid
    if (this != nullptr)
    {
        // Clear the debug information field (offset +0x00)
        this->DebugInfo = nullptr;
        // Initialize with spin count to reduce context switches
        InitializeCriticalSectionAndSpinCount(this, 10);
    }
}