// FUNC_NAME: UIManager::checkButtonRolloverSound
char UIManager::checkButtonRolloverSound(byte* buttonPath)
{
    bool found = false;
    uint buttonIndex = 0;
    // Check first two buttons (index 0 and 1)
    do {
        if (1 < buttonIndex) {
            return found;
        }
        // Generate expected button path: "/gurd/buttons/button_%d/button"
        char pathBuffer[64];
        FUN_00910160(pathBuffer, "/gurd/buttons/button_%d/button", buttonIndex);
        // Compare pathBuffer with buttonPath
        byte* pBuffer = pathBuffer;
        byte* pInput = buttonPath;
        int cmpResult;
        do {
            byte b = *pBuffer;
            bool less = b < *pInput;
            if (b != *pInput) {
                cmpResult = (1 - (uint)less) - (uint)(less != 0);
                break;
            }
            if (b == 0) {
                cmpResult = 0;
                break;
            }
            b = pBuffer[1];
            less = b < pInput[1];
            if (b != pInput[1]) {
                cmpResult = (1 - (uint)less) - (uint)(less != 0);
                break;
            }
            pBuffer += 2;
            pInput += 2;
        } while (b != 0);
        if (cmpResult == 0) {
            // Build sound event path using a second format string (e.g., rollover path)
            FUN_00910160(pathBuffer, &DAT_00e3266c, buttonIndex);
            // Play rollover sound: "RollOverButton" event with pathBuffer as argument
            FUN_005a04a0("RollOverButton", 0, &DAT_00d8a1e4, 1, pathBuffer);
            found = true;
            // Initialize some structure (color/transform?)
            local_4c = DAT_011302b0;
            local_48 = 0;
            local_44 = 0;
            FUN_00408a00(&local_4c, 0);
        }
        buttonIndex++;
        if (found) {
            return found;
        }
    } while (true);
    return found;
}