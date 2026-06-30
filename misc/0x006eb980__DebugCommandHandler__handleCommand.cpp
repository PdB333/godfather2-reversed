// FUNC_NAME: DebugCommandHandler::handleCommand
// Address: 0x006eb980
// Purpose: Dispatches debug console commands based on command ID.
// param_2 (commandId) is the command/action ID.
// param_3 (data) is a pointer to a command data structure containing two pointers at offsets 0 and 8.
// The actual objects are obtained by subtracting 0x48 from these pointers.

void DebugCommandHandler::handleCommand(this, uint32 commandId, int* data) {
    // Check data validity: data not null, both pointers non-null and not the magic invalid value 0x48
    if (data == nullptr || *data == 0 || *data == 0x48) {
        return;
    }

    int* subData = data + 2; // data[2]
    if (subData == nullptr || *subData == 0 || *subData == 0x48) {
        return;
    }

    // Derive base objects by subtracting the header offset 0x48
    int* mainObj = reinterpret_cast<int*>(*data - 0x48);
    int* subObj  = reinterpret_cast<int*>(*subData - 0x48);

    switch (commandId) {
    case 8: { // ID_8: likely "activate cheat"
        int state = isObjectActive(mainObj); // 0x006ad770
        if (state != 0) {
            printDebugMessage(); // 0x0078b0c0
            return;
        }
        break;
    }
    case 0x23: { // ID_0x23: "activate something with hash"
        int entity = getObjectByHash(mainObj, 0x369ac561); // 0x006bc8d0
        if (entity != 0) {
            playSoundEffect(); // 0x0072f400
        }
        // Fall through to generic handler
        // No break; intentionally falls through to cases 3,0x24,0x26...
        goto genericHandler;
    }
    case 3:
    case 0x24:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2c:
    case 0x2d:
    case 0x2e: {
        genericHandler: {
            // Build a local structure containing the command ID
            uint32 local_14 = commandId;
            uint32 local_10 = 0;
            uint32 local_c = 0;
            uint32 local_8 = 0;
            uint32 local_4 = 0;

            releaseCommandData(data);    // 0x006ccd70
            releaseCommandData(subData); // 0x006ccd70
            sendCommandToSystem(&local_14); // 0x006f89c0
            handleCommandResult();        // 0x006eb7d0
            break;
        }
    }
    case 0x30: // ID_0x30: "set scale to 1.0"
        setFloatScale(mainObj, 1.0f); // 0x006eb900
        return;
    case 0x31: // ID_0x31: "set volume to 1.0"
        setFloatVolume(mainObj, 1.0f); // 0x006eb720
        return;
    case 0x39: { // ID_0x39: "feature A with nested checks"
        int someEntity = getObject(mainObj); // 0x006bc8b0
        if (someEntity == 0 || !isFeatureAEnabled()) { // 0x006eb960
            break;
        }

        // Re-fetch the entity? Possibly a different one
        int entityWithHash = getObjectByHash(mainObj, 0x369ac561); // 0x006bc8d0
        if (entityWithHash != 0) {
            int mode = getGameMode(); // 0x00806440
            if (mode == 3 && *(uint32*)(entityWithHash + 0x1ed0) > 2) { // +0x1ed0: some count/array length
                int device = getInputDevice(); // 0x007351c0
                setDeviceVibration(device);    // 0x008c6db0
            }
        }

        int objOrNull = (*data != 0) ? reinterpret_cast<int*>(*data - 0x48) : nullptr;
        int entityType = getEntityType(objOrNull); // 0x006ad7f0
        if (*data != 0) {
            applyModifier(reinterpret_cast<int*>(*data - 0x48), entityType, 1); // 0x009b1e40
        } else {
            applyModifier(0, entityType, 1); // 0x009b1e40
        }
        return;
    }
    case 0x3a: { // ID_0x3a: "feature B"
        int someEntity = getObject(mainObj); // 0x006bc8b0
        if (someEntity != 0 && isFeatureBEnabled()) { // 0x006eb940
            setGlobalState(1); // 0x009b1970
            return;
        }
        break;
    }
    case 0x47: { // ID_0x47: "toggle debug flag"
        int debugObj = getDebugObject(mainObj); // 0x006eb8b0
        if (debugObj != 0 && isDebugModeEnabled()) { // 0x00782ce0
            int active = isObjectActive(mainObj); // 0x006ad770
            uint8 flag = (active != 0) ? getDebugBool() : 0; // 0x0078af40
            if (*data != 0) {
                setDebugBool(reinterpret_cast<int*>(*data - 0x48), flag); // 0x00782db0
            } else {
                setDebugBool(0, flag);
            }
            return;
        }
        break;
    }
    case 0x49: // ID_0x49: "toggle fullscreen"
        toggleFullscreen(); // 0x00929af0
        return;
    case 0x4b: { // ID_0x4b: "enable something based on flag"
        int someEntity = getObject(mainObj); // 0x006bc8b0
        int derivedObj = (*subData != 0) ? reinterpret_cast<int*>(*subData - 0x48) : nullptr;
        if (someEntity != 0 && (*(uint8*)(someEntity + 0x45) & 1) != 0) { // +0x45: bitmask field
            int device = getInputDevice(); // 0x007351c0
            bool ready = isDeviceReady(device); // 0x006eb790
            if (!ready && isOptionSet()) { // 0x0090b180
                if (*data != 0) {
                    enableOption(derivedObj, reinterpret_cast<int*>(*data - 0x48)); // 0x0090b220
                } else {
                    enableOption(derivedObj, 0);
                }
                return;
            }
        }
        break;
    }
    case 0x5a: { // ID_0x5a: "execute action on subObj"
        if (subObj != 0 && checkAccess(1)) { // 0x00911f40
            executeAction(subObj); // 0x009263b0
            return;
        }
        break;
    }
    case 0x5c: // ID_0x5c: "reset something"
        resetSettings(); // 0x007cc3b0
        return;
    case 0x5e: // ID_0x5e: "exit application"
        exitApp(); // 0x00929b10
        return;
    default:
        break;
    }
    return;
}