// FUNC_NAME: GodfatherGameManager::handleEvent
int __thiscall GodfatherGameManager::handleEvent(int this, int eventData) {
    char isReady;
    int result;
    // Check if bit 1 of flag at offset 0x249c is set
    if ((*(uint *)(this + 0x249c) >> 1 & 1) != 0) {
        isReady = FUN_00481620(); // Check if system is ready (global function)
        if (isReady != '\0') {
            // Dispatch event using type byte at offset 0x2498
            result = FUN_00466060(*(byte *)(this + 0x2498), eventData);
            return result;
        }
    }
    return 1; // Default success
}