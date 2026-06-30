// FUNC_NAME: SimManager::resolveObjectFromString
// Function at 0x005bc230 - resolves an object by name string, with type-dependent dispatch
uint* __thiscall SimManager::resolveObjectFromString(uint* thisPtr, char* objectName)
{
    char c;
    uint* contextPtr;
    uint* result;
    int type;

    char* pName = objectName;
    if (thisPtr == (uint*)0x0) {
        thisPtr = thisPtr;  // should be in_EAX = thisPtr; but effectively same
    }
    // Get length of string
    do {
        c = *pName;
        pName = pName + 1;
    } while (c != '\0');

    contextPtr = getTypeContext();  // FUN_005bc0f0 - returns pointer to context block
    if (contextPtr == (uint*)0x0) {
        // No context: use objectName as direct lookup
        if ((~(byte)(*thisPtr >> 0xf) & 1) == 0) {  // check bit 15 flag on this
            type = getCurrentPlayer();  // FUN_005bc1e0
            if ((type == 0) || (result = hashTableLookup(type, objectName), result == (uint*)0x0)) {  // FUN_005bb050
                result = hashTableLookup(DAT_0119cbb8 + 1, objectName);
            }
            return result;
        }
    }
    else {
        type = *(int*)(contextPtr + 4);  // type field at offset +4
        switch(type) {
        case 1:
            break;
        case 2:
            result = getPlayerManager();  // FUN_005b94c0
            if (result != thisPtr) {
                getCurrentPlayer();
                result = getPlayerManager();
                return result;
            }
            return thisPtr;
        case 3:
            c = isInGame(0);  // FUN_0059c5c0
            if (c != '\0') {
                uint* listStart = getSimObjectList();  // FUN_0059c3b0
                result = (uint*)listStart[0x15];  // offset 0x54?
                if (result == (uint*)0x0) {
                    return listStart;
                }
                do {
                    listStart = result;
                    result = (uint*)result[0x15];
                } while (result != (uint*)0x0);
                return listStart;
            }
            break;
        default:
            if (((5 < type) && (type < 0x24)) || ((0x25 < type) && (type < 0x72))) {
                atoi(objectName + 6);  // skip "object" or similar prefix? _atol
                result = (uint*)lookupByNumericId();  // FUN_0059e2f0
                return result;
            }
            unknownFallback();  // FUN_0059bf00
            break;
        case 5:
            return DAT_0119cbb0;
        case 0x10:
            c = isInGame(0);
            if (c != '\0') {
                int listBase = getSimObjectList();
                return *(uint**)(listBase + 0x54);  // maybe current player object
            }
            break;
        case 0x11:
            return DAT_0119cc0c;
        case 0x12:
            getPlayerManager();
            getCurrentPlayer();
            return DAT_0119cbbc;
        case 0x13:
            return DAT_0119cbb8;
        }
    }
    return (uint*)0x0;
}