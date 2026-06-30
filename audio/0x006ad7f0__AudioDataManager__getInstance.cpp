// FUNC_NAME: AudioDataManager::getInstance
// Function at 0x006ad7f0: Returns the global AudioDataManager instance if requested, or null if creation is suppressed.
// param_1 is a boolean flag (bCreateIfMissing): if non-zero, ensures the manager is created and returns it; otherwise returns 0.
int AudioDataManager::getInstance(bool bCreateIfMissing)
{
    if (bCreateIfMissing) {
        return FUN_0043b870(DAT_01130fa0); // create/retrieve the singleton at global pointer 0x01130fa0
    }
    return 0;
}