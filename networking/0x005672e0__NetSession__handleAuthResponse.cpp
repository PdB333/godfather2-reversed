// FUNC_NAME: NetSession::handleAuthResponse
void __thiscall NetSession::handleAuthResponse(int thisPtr, int responseData)
{
    char *pcVar1;
    char cVar2;
    undefined4 uVar3;
    char *pcVar4;
    char versionBuffer[32];

    // Check if response data is valid
    if (responseData != 0) {
        // Check for Plasma error condition
        cVar2 = PlasmaCheckForErrors();
        if (cVar2 != '\0') {
            uVar3 = PlasmaGetLastError();
            LogError(uVar3, "Plasma GetTOS returned an error");
            *(undefined4 *)(thisPtr + 0x10) = 9; // Set state to error (9)
            return;
        }

        // Attempt to read the "version" configuration string (max 32 chars)
        cVar2 = GetConfigurationString("version", versionBuffer, 0x20);
        if (cVar2 == '\0') {
            versionBuffer[0] = 0; // Clear buffer on failure
        }

        // Free previous version string if one exists
        if (*(int *)(thisPtr + 0x20) != 0) {
            *(undefined4 *)(thisPtr + 0x24) = 0;
            MemoryFree(*(int *)(thisPtr + 0x20));
        }

        // Copy the version string from response data (at offset 0xc)
        pcVar4 = *(char **)(responseData + 0xc);
        pcVar1 = pcVar4 + 1;
        do {
            cVar2 = *pcVar4;
            pcVar4 = pcVar4 + 1;
        } while (cVar2 != '\0');
        *(int *)(thisPtr + 0x24) = (int)pcVar4 - (int)pcVar1; // String length
        uVar3 = MemoryAlloc(((int)pcVar4 - (int)pcVar1) + 1);
        *(undefined4 *)(thisPtr + 0x20) = uVar3;
        GetConfigurationString(&DAT_00e3a5e0, uVar3, *(undefined4 *)(thisPtr + 0x24));
        *(undefined1 *)(*(int *)(thisPtr + 0x24) + *(int *)(thisPtr + 0x20)) = 0; // Null-terminate

        // Check flag at +0x2c bit 2 (value 4)
        if ((*(uint *)(thisPtr + 0x2c) >> 2 & 1) == 0) {
            // Flag not set: set state to processing/ok (0) and sub-state to 2
            *(undefined1 *)(thisPtr + 0x14) = 2;
            *(undefined4 *)(thisPtr + 0x10) = 0;
            return;
        }
        // Flag set: set state to 8 (challenge response received?)
        *(undefined4 *)(thisPtr + 0x10) = 8;
    }
    return;
}