// FUNC_NAME: initCriticalSection
LPCRITICAL_SECTION initCriticalSection(LPCRITICAL_SECTION criticalSection)
{
    // Calls Windows API to initialize a critical section object.
    InitializeCriticalSection(criticalSection);
    return criticalSection; // Allows use in initialization lists or assignment.
}