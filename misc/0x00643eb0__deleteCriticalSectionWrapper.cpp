// FUNC_NAME: deleteCriticalSectionWrapper
void deleteCriticalSectionWrapper(void)
{
    // in_EAX: pointer to a CRITICAL_SECTION to be deleted
    LPCRITICAL_SECTION criticalSection = (LPCRITICAL_SECTION)in_EAX;
    DeleteCriticalSection(criticalSection);
    return;
}