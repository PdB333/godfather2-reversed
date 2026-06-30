// FUNC_NAME: ArchiveLoader::processHaltCheck
// Function at 0x00568a70: Checks locale code in archive data and sets a halt flag accordingly.
// This appears to be a step in an asynchronous loading state machine for archive/package files.
// Uses key-value archive operations with keys "cdbl", "locl", "halt".
// State transitions: 2 -> 3 -> (4 or stays 3) -> callback.

void __thiscall ArchiveLoader::processHaltCheck(int thisPtr, undefined4 callbackData)
{
    char cancelFlag;
    int stateCheck;
    char *foundPos;

    // Check if overall operation has been cancelled
    cancelFlag = isCancelRequested();
    if (cancelFlag == '\0') {
        // Only proceed if current state is 2
        if (*(int *)(thisPtr + 0xc) != 2) {
            return;
        }
        // Perform some action with callback data (maybe prepare context)
        somePrepareCall(callbackData);
        // Retrieve large data block associated with key "cdbl" (0x6364626c) into local buffer
        archiveGetValue(*(undefined4 *)(thisPtr + 4), 0x6364626c, 0, local_408);  // "cdbl"
        // Get a string key for further lookup (e.g., locale key)
        stateCheck = archiveGetString(*(undefined4 *)(thisPtr + 4), local_908);
        if ((stateCheck == 0) && (stateCheck = archiveGetCount(*(undefined4 *)(thisPtr + 4)), 0 < stateCheck)) {
            // Transition to state 3 (loaded)
            *(undefined4 *)(thisPtr + 0xc) = 3;
            // Retrieve a 4-byte value for key "locl" (0x6c6f636c) – likely a locale code
            archiveGetRaw(*(undefined4 *)(thisPtr + 4), 0x6c6f636c, local_90c, 4);  // "locl"
            // Search for that locale code in the large data block
            foundPos = _strstr(local_408, local_90c);
            if (foundPos == (char *)0x0) {
                // If not found there, search in an alternate buffer (local_808, possibly preloaded)
                foundPos = _strstr(local_808, local_90c);
                if (foundPos == (char *)0x0) {
                    // Not found in either – set halt to 1 and advance state to 4 (failure?)
                    archiveSetValue(*(undefined4 *)(thisPtr + 4), 0x68616c74, 1, 0);  // "halt"
                    *(undefined4 *)(thisPtr + 0xc) = 4;
                }
                else {
                    // Found in alternate buffer – set halt to 0 (success)
                    archiveSetValue(*(undefined4 *)(thisPtr + 4), 0x68616c74, 0, 0);  // "halt"
                }
            }
            else {
                // Found in primary buffer – set halt to 1 (success but different handling)
                archiveSetValue(*(undefined4 *)(thisPtr + 4), 0x68616c74, 1, 0);  // "halt"
            }
            // If a callback function pointer exists, invoke it with the user data from thisPtr+8
            if (DAT_0119a5b4 != (code *)0x0) {
                (*DAT_0119a5b4)(*(undefined4 *)(thisPtr + 8));
            }
            return;
        }
    }
    // On cancellation or failure, set state to 5 (error/abort)
    *(undefined4 *)(thisPtr + 0xc) = 5;
    return;
}