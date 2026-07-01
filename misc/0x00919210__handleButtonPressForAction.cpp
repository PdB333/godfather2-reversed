// FUNC_NAME: handleButtonPressForAction
char handleButtonPressForAction(byte *buttonPath)
{
    char result = '\0';
    uint buttonIndex = 0;
    char formattedPath[64];

    do {
        if (2 < buttonIndex) {
            return result;
        }
        // Build button path like "/comm/buttons/button_0/button"
        formatPath(formattedPath, "/comm/buttons/button_%d/button", buttonIndex);
        
        // Compare the built path with the given buttonPath (string comparison, two bytes at a time)
        byte *src = formattedPath;
        byte *dst = buttonPath;
        int cmpResult;
        do {
            byte bVar1 = *src;
            bool bVar7 = bVar1 < *dst;
            if (bVar1 != *dst) {
                cmpResult = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                goto cmp_done;
            }
            if (bVar1 == 0) break;
            bVar1 = src[1];
            bVar7 = bVar1 < dst[1];
            if (bVar1 != dst[1]) {
                cmpResult = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
                goto cmp_done;
            }
            src += 2;
            dst += 2;
        } while (bVar1 != 0);
        cmpResult = 0;
cmp_done:
        if (cmpResult == 0) {
            // Match found, build action path (e.g., "/comm/buttons/button_%d/action")
            formatPath(formattedPath, g_actionPathFormat, buttonIndex);
            // Trigger the button action with event name "RollOutButton"
            sendUIEvent("RollOutButton", 0, g_buttonActionString, 1, formattedPath);
            result = '\x01';
        }
        buttonIndex++;
        if (result != '\0') {
            return result;
        }
    } while (true);
}