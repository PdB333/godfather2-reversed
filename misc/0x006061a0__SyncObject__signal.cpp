// FUNC_NAME: SyncObject::signal
void SyncObject::signal() {
    LPCRITICAL_SECTION criticalSection = g_pSyncCriticalSection;

    EnterCriticalSection(criticalSection);

    // Clear the high bit (likely 'signaled' or 'waiting' flag)
    g_syncFlags &= 0x7fffffff;
    g_syncState = 4; // Set state to "signaled"

    // If all waiters have been accounted for (maxWaiters == 0x3f) and no one is waiting,
    // and no pending signals, reset maxWaiters to allow reuse
    if ((g_maxWaiters == 0x3f) && (g_waitCount == 0) && (g_syncFlags == 0)) {
        g_maxWaiters = 0x40; // Reset to initial non-full state
    }

    LeaveCriticalSection(criticalSection);
}