// FUNC_NAME: AudioDataManager::releaseBankHandle
void AudioDataManager::releaseBankHandle(void)
{
    // Call free/release function with the current handle
    FUN_0043c200(DAT_00e52798);
    // Invalidate the handle (0xffffffff = -1, common sentinel value)
    DAT_00e52798 = 0xffffffff;
    return;
}