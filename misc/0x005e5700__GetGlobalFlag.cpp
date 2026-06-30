// FUNC_NAME: GetGlobalFlag
// Function at 0x005e5700: Retrieves a global flag from a manager/singleton at address DAT_01223514 using offset 0.
// Returns the value at that offset (as an int), or 0 if the pointer is null.

int GetGlobalFlag(void)
{
    uint8_t flagOffset = 0; // Offset/index into the global data structure
    int32_t *pFlag = (int32_t *)FUN_005f0600(DAT_01223514, &flagOffset);
    if (pFlag != nullptr) {
        return *pFlag;
    }
    return 0;
}