// FUNC_NAME: maybePlayNotification

void maybePlayNotification(void)
{
    // Global singleton pointer, likely to a manager (e.g., DialogTreeManager or AudioDataManager)
    // +0x0C: boolean flag or pointer indicating if something is active
    if ((g_pSomeManager != (void*)0x0) && (*(int*)((int)g_pSomeManager + 0xC) != 0)) {
        // Send event/play sound at priority 7 using the string/data at PTR_LAB_00d79770
        sendEvent(&PTR_LAB_00d79770, 7);
    }
}