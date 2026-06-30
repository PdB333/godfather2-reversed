// FUNC_NAME: Sentient::checkActionCondition
// Function address: 0x00748b00
// Checks whether a given action (actionId) is allowed based on various conditions.
// Offsets used:
//   +0x30: float, likely a distance/cooldown value
//   +0x50: void*, likely a pointer to an entity or object
//   +0x58: int*, pointer to a derived class (offset -0x48 to get base)
//   +0x60: probably a position/vector3 (used for distance/los)
//   +0x6c: another position/vector3
//   +0x40 (in derived): flags byte (bit0 = some flag)
//   +0x1e4 (in derived): char, likely a cooldown flag

enum ActionId : int {
    ACTION_DISTANCE_CHECK_1   = 10, // +0.60 distance
    ACTION_DISTANCE_CHECK_2   = 11, // +0.6c distance
    ACTION_LOS_CHECK          = 12, // line of sight
    ACTION_FLAG_CHECK         = 13, // flag & cooldown
    ACTION_GLOBAL_CONDITION   = 14, // some global condition
    ACTION_PLAYER_VEHICLE_BIT = 15, // player & vehicle control bit
    ACTION_TIMER_CHECK        = 16  // time-based condition
};

bool __thiscall Sentient::checkActionCondition(int self, int unk1, int unk2, int actionId, int unk3) {
    bool result = false;
    float distance1;
    float distance2;
    int derivedPtr;
    int derivedBase;
    int targetIndex;
    char losResult;
    void* targetObj;

    switch (actionId - 10) {
    case 0: // actionId == 10
        distance1 = getPositionDistance(self + 0x60); // FUN_004702b0
        if (DAT_00d5c454 < distance1) {  // global threshold < distance
            result = true;
        }
        break;

    case 1: // actionId == 11
        distance2 = getPositionDistance(self + 0x6c); // FUN_004702b0
        if (DAT_00d5c454 < distance2) {
            result = true;
        }
        break;

    case 2: // actionId == 12
        if (*(int*)(self + 0x58) == 0) {
            derivedPtr = 0;
        } else {
            derivedPtr = *(int*)(self + 0x58) - 0x48;
        }
        if (*(char*)(derivedPtr + 0x1e4) != '\0') {
            result = false;
            break;
        }
        targetIndex = getCurrentVehicleId(); // FUN_00471610
        losResult = checkLineOfSight(self + 0x60, targetIndex + 0x30, 1, 0); // FUN_0080e650
        result = (losResult == '\0'); // true if line of sight clear
        break;

    case 3: // actionId == 13
        if (*(int*)(self + 0x58) == 0) {
            result = true;
            break;
        }
        if (*(int*)(self + 0x58) == 0x48) {
            result = true;
            break;
        }
        if (*(int*)(self + 0x58) == 0) {
            derivedPtr = 0;
        } else {
            derivedPtr = *(int*)(self + 0x58) - 0x48;
        }
        result = true;
        if ((*(byte*)(derivedPtr + 0x40) & 1) != 0) {
            if (*(int*)(self + 0x58) == 0) {
                derivedBase = 0;
            } else {
                derivedBase = *(int*)(self + 0x58) - 0x48;
            }
            if (*(char*)(derivedBase + 0x1e4) == '\0') {
                result = false;
            }
        }
        break;

    case 4: // actionId == 14
        result = isTargetValid(); // FUN_00748460
        break;

    case 5: // actionId == 15
        if (isPlayerControlled() != '\0') { // FUN_007f47a0
            targetObj = getEntityByHandle(*(void**)(self + 0x50)); // FUN_0072dc00
            if (targetObj != 0) {
                result = (*(uint*)(targetObj + 0x4c) >> 1) & 1;
            }
        }
        break;

    case 6: // actionId == 16
        if (DAT_00d5eee4 <= *(float*)(self + 0x30)) {
            result = true;
        }
        break;

    default:
        result = baseCheckActionCondition(unk1, unk2, actionId, unk3); // FUN_004ac640
        break;
    }
    return result;
}