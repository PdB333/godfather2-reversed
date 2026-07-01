// FUNC_NAME: PlayerController::canPerformAction
bool __thiscall PlayerController::canPerformAction(uint* actionIdRef) {
    uint actionId = *actionIdRef;
    bool result = false;
    
    // Check if action ID is in the range [6, 9] (i.e., 6, 7, 8, 9)
    if ((actionId > 5) && (actionId < 10)) {
        // Check if bit 7 of flags at offset 0xA18 is set, or if action is not 8 or 9
        // (action IDs 8 and 9 require the flag; IDs 6 and 7 are always allowed)
        if (((*(uint*)(this + 0xA18) >> 7) & 1) || 
            (actionId != 8 && actionId != 9)) {
            result = true;
        }
    }
    
    return result;
}