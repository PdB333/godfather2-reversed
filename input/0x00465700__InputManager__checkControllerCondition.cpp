// FUNC_NAME: InputManager::checkControllerCondition
bool InputManager::checkControllerCondition(int condition) {
    // condition lower byte used, 0x10-0x14 are special checks
    unsigned char request = (unsigned char)(condition & 0xFF);
    if (request != 0x12) { // not kConditionNone
        if (request < 0x10) {
            // Check a specific controller slot (0-15)
            char result = isControllerSlotActive(request);
            if (result != 0) {
                return true;
            }
        } else {
            // Count active slots (0-15)
            unsigned char slot = 0;
            int activeCount = 0;
            do {
                char result = isControllerSlotActive(slot);
                if (result != 0) {
                    activeCount++;
                }
                slot++;
            } while (slot < 0x10);

            switch (request) {
                case 0x11: // kConditionAll
                    if (activeCount == 16) {
                        return true;
                    }
                    break;
                case 0x12: // kConditionNone (already handled above, but just in case)
                    return false;
                case 0x13: // kConditionAny
                    if (activeCount > 0) {
                        return true;
                    }
                    break;
                case 0x14: // kConditionTwo
                    if (activeCount == 2) {
                        return true;
                    }
                    break;
            }
        }
    }
    return false;
}