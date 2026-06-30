// FUNC_NAME: deleteCriticalSection
// Address: 0x00643eb0
// Role: Wrapper function to delete a Windows critical section.
// The critical section pointer is passed in EAX (__fastcall with first param in EAX?).
void deleteCriticalSection(LPCRITICAL_SECTION criticalSection)
{
    DeleteCriticalSection(criticalSection);
}