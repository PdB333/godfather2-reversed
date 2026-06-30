// FUNC_NAME: SimObject::handleMessage
bool __thiscall SimObject::handleMessage(int *thisObj, int unusedParam, int param3, int param4, uint flags)
{
    bool success;
    
    // Check if the game is paused or in some exclusive mode
    bool isSystemSuspended = FUN_00842880(); // Likely isGamePaused() or isNetworkGame()
    if (isSystemSuspended == false) {
        // Check if this object is still alive or not destroyed
        bool isObjectDestroyed = FUN_006f08e0(); // Likely isObjectMarkedForDelete()
        if (isObjectDestroyed == false) {
            // Magic numbers for a special "uninitialized" or "default" message type
            // 0xBADBDBBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
            bool isSpecialMessage = (
                (*thisObj == 0xBADBDBBA && thisObj[1] == 0xBEEFBEEF &&
                 thisObj[2] == 0xEAC15A55 && thisObj[3] == 0x91100911)
            );
            bool isNullMessage = (
                (*thisObj == 0 && thisObj[1] == 0 &&
                 thisObj[2] == 0 && thisObj[3] == 0)
            );
            // Only process messages that are neither special nor null
            if (!isSpecialMessage && !isNullMessage) {
                // Retrieve the handler / component manager for this object type
                int handler = FUN_00446100(thisObj, 0); // e.g. getComponentManager()
                if (handler != 0 && thisObj[4] != 0) { // thisObj[4] is payload pointer
                    // Build flags: set bit 2 if thisObj[5] (byte) is non-zero
                    uint extraFlags = (uint)((char)thisObj[5] != 0) ? 4 : 0;
                    uint finalFlags = extraFlags | flags;
                    // Dispatch the message (vtable call or direct handler call)
                    success = FUN_006f77a0(
                        handler, thisObj[4], param4, param3,
                        finalFlags, 0, 0
                    ) != 0;
                    return success;
                }
            }
        }
    }
    return false;
}