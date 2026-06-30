// FUNC_NAME: PlayerSM::handleStateCommand
bool __thiscall PlayerSM::handleStateCommand(int *thisObj, int arg1, int arg2, int arg3, int commandId, int arg5)
{
    char byteVal;
    bool result = true;

    switch (commandId - 0x12) {
    case 0: // commandId == 0x12: SetState0
        *(char *)(thisObj + 0x19) = 0; // +0x19: some state flag
        return true;

    case 1: // commandId == 0x13
    case 0xB: // commandId == 0x1D
        break; // fall through to default? Actually break returns result (true)

    case 2: // commandId == 0x14: CheckFloatCondition
        if (*(float *)0x00d5c458 < (float)thisObj[0xC]) { // +0x0C: some float threshold
            FUN_009b2510(); // reset condition or trigger game logic
            return true;
        }
        break;

    case 3: // commandId == 0x15: SetState1
        *(char *)(thisObj + 0x19) = 1; // +0x19: set flag
        return true;

    case 4: // commandId == 0x16: CleanupState
        FUN_00745270(); // state cleanup
        return true;

    case 5: // commandId == 0x17: CreateObjectFromHash
        {
            int idx = thisObj[0x1A]; // +0x1A: some index
            int base = thisObj[0x16]; // +0x16: base pointer?
            int obj = FUN_00624bd0(0x1B2D5C51); // hash lookup, returns object handle
            FUN_007450e0(obj, base, idx); // attach object
            return true;
        }

    case 6: // commandId == 0x18: EnableFlagAndUpdate
        FUN_009b24d0(); // update something
        FUN_004abdd0(0x40000); // set global flag (e.g., enable gravity?)
        return true;

    case 7: // commandId == 0x19: PlayIfAllowed
        byteVal = FUN_00745010(); // check if allowed
        if (byteVal && thisObj[0x1C] != 0 && thisObj[0x1C] != 0x50) { // +0x1C: resource counter or ID
            char buf[12];
            FUN_009b2ad0(buf); // get sound context
            if (thisObj[0x1C] != 0) {
                FUN_0075b4f0(buf); // play sound
                return true;
            }
            FUN_0075b4f0(buf);
            return true;
        }
        break;

    case 8: // commandId == 0x1A: ReleaseResource
        if (thisObj[0x1C] != 0) {
            FUN_004daf90(thisObj + 0x1C); // release or decrement
            thisObj[0x1C] = 0;
            return true;
        }
        break;

    case 9: // commandId == 0x1B: EnableAudio
        if (*(char *)&thisObj[0x1E] == 0) { // +0x1E: audio enabled flag
            FUN_007f62b0(); // start audio system
            FUN_007f6db0(0); // set volume?
            *(char *)&thisObj[0x1E] = 1; // mark enabled
            return true;
        }
        break;

    case 10: // commandId == 0x1C: DisableAudio
        if (*(char *)&thisObj[0x1E] != 0) {
            FUN_007f6300(0); // stop/disable audio
            *(char *)&thisObj[0x1E] = 0;
            return true;
        }
        break;

    case 0xC: // commandId == 0x1E: SetupCamera
        {
            float one = 1.0f;
            int cam = FUN_007347e0(); // get camera object
            (*(code **)(*(int *)cam + 0x2C))(cam, 1, 0, 0, one, one); // call camera method (vtable offset 0x2C)
            char val = FUN_00690150(1); // check game state
            *(char *)((int)thisObj + 0x66) = val; // store state
            return true;
        }

    case 0xD: // commandId == 0x1F: CheckCameraTransition
        char storedVal = *(char *)((int)thisObj + 0x66);
        char newVal = FUN_00690150(1);
        if (storedVal == newVal) {
            if (newVal == 0) {
                FUN_0072fbf0(); // maybe reset camera
                return true;
            }
            // else do nothing
        } else {
            // state changed
            *(char *)((int)thisObj + 0x66) = newVal;
            int cam = FUN_007347e0();
            char transitionActive = FUN_0045eec0(cam); // check if transition in progress
            if (transitionActive == 0) {
                (*(code **)(*(int *)cam + 0x2C))(cam, 1, 0, 0, 1.0f, 1.0f);
                return true;
            }
        }
        break;

    case 0xE: // commandId == 0x20: SyncTransformToVehicle
        if (thisObj[0x17] != 0 && thisObj[0x17] != 0x48) { // +0x17: vehicle ID?
            int vehicleTransform = FUN_00471610(); // get vehicle transform
            int playerTransform = thisObj[0x1A]; // +0x1A: player transform pointer?
            // copy 12 bytes (position + orientation?) from vehicle to player
            *(int64_t *)(playerTransform + 0x30) = *(int64_t *)(vehicleTransform + 0x30);
            *(int *)(playerTransform + 0x38) = *(int *)(vehicleTransform + 0x38);
            *(short *)(playerTransform + 0x78) |= 0x20; // set flag
        }
        FUN_007f6420(0x62); // play sound 0x62 (e.g., engine)
        return true;

    case 0xF: // commandId == 0x21: StopVehicleSound
        FUN_007f63e0(0x62); // stop sound 0x62
        return true;

    case 0x10: // commandId == 0x22: DetonateIfValid
        if (thisObj[0x1C] != 0 && thisObj[0x1C] != 0x50) {
            int physicsObj = FUN_006e6410(); // get physics/destruction manager
            if (thisObj[0x1C] != 0) {
                FUN_0075bc60(physicsObj); // detonate
                return true;
            }
            FUN_0075bc60(physicsObj);
            return true;
        }
        break;

    default:
        result = FUN_0080e8e0(arg1, arg2, arg3, commandId, arg5); // base class handler
    }

    return result;
}