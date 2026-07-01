// FUNC_NAME: InputManager::handleButtonAction
char __thiscall InputManager::handleButtonAction(int thisPtr, char *buttonName)
{
    char result = '\0';
    
    // Check if input is disabled (likely a flag at +0x50)
    if (*(int *)(thisPtr + 0x50) != 0) {
        return '\0';
    }
    
    uint buttonIndex = 0;
    do {
        if (2 < buttonIndex) {
            return result;
        }
        
        // Build path like "/ctrl/buttons/button_%d/button" with current index
        char path[64];
        FUN_00910160(path, "/ctrl/buttons/button_%d/button", buttonIndex);
        
        // Compare the built path with the input button name
        char *pPath = path;
        char *pName = buttonName;
        int cmpResult;
        
        do {
            char c1 = *pPath;
            char c2 = *pName;
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            c1 = pPath[1];
            c2 = pName[1];
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            pPath += 2;
            pName += 2;
        } while (c1 != 0);
        
        if (cmpResult == 0) {
            // Match found - build the full path and call the rollout function
            FUN_00910160(path, "/ctrl/buttons/button_%d/button", buttonIndex);
            FUN_005a04a0("RollOutButton", 0, &DAT_00d87288, 1, path);
            result = '\x01';
        }
        
        buttonIndex++;
        if (result != '\0') {
            return result;
        }
    } while (true);
}