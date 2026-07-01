// FUNC_NAME: ProcessPendingDeletions
void ProcessPendingDeletions(void)
{
    if (g_pPendingDestroy1 != 0) {
        DestroyPending();
    }
    if (g_pPendingDestroy2 != 0) {
        DestroyPending();
        return;
    }
    return;
}