// FUNC_NAME: MissionCondition::evaluateEvent

#include <cstdint>

// Forward declarations
class Entity;
class Player;
extern float gSquaredDistanceThreshold; // DAT_00d640a4
extern int gSomeGlobalIndex;            // DAT_00e52468

// External functions
Entity* getPlayerEntity(void);                                    // FUN_00471610
bool checkGameFlag(int flagId);                                   // FUN_00690150
bool isPositionValid(float* position);                            // FUN_00718d40
bool checkSomething(int index, int constant);                     // FUN_0043c6c0
bool defaultEventHandler(undefined4 param2, undefined4 param3, int eventType, undefined4 param5); // FUN_004ac640

class MissionCondition {
public:
    // Offset schema:
    // +0x50: pointer to something (probably another entity/player)
    // +0x54: state/type (0 or 0x48 indicate valid states)
    // +0x5c: sub-type (1 or 2)
    // +0x1ed4: some ID field in the referenced object

    bool evaluateEvent(undefined4 param2, undefined4 param3, int eventType, undefined4 param5) {
        // eventType is offset by 10 in the switch
        switch (eventType - 10) {
        case 0: // eventType == 10
            // Check if state is 0 or 0x48 => return true if so
            if (*(int*)(this + 0x54) == 0 || *(int*)(this + 0x54) == 0x48) {
                return true;
            }
            break;

        case 1: // eventType == 11
            {
                Entity* entity1 = getPlayerEntity();
                Entity* entity2 = getPlayerEntity();
                float dx = *(float*)(entity2 + 0x30) - *(float*)(entity1 + 0x30);
                float dy = *(float*)(entity2 + 0x34) - *(float*)(entity1 + 0x34);
                float dz = *(float*)(entity2 + 0x38) - *(float*)(entity1 + 0x38);
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq < gSquaredDistanceThreshold) {
                    return true;
                }
            }
            break;

        case 2: // eventType == 12
            // State must not be 0 or 0x48, and a game flag must be set
            if (*(int*)(this + 0x54) != 0 && *(int*)(this + 0x54) != 0x48) {
                if (checkGameFlag(0x15)) {
                    return true;
                }
            }
            break;

        case 3: // eventType == 13
            // State must not be 0 or 0x48, then check position validity
            if (*(int*)(this + 0x54) != 0 && *(int*)(this + 0x54) != 0x48) {
                Entity* entity = getPlayerEntity();
                if (!isPositionValid((float*)(entity + 0x30))) {
                    return true;
                }
            }
            break;

        case 4: // eventType == 14
            {
                int subType = *(int*)(this + 0x5c);
                if (subType == 1) {
                    int index;
                    if (*(int*)(this + 0x54) == 0) {
                        index = 0;
                    } else {
                        index = *(int*)(this + 0x54) - 0x48;
                    }
                    if (!checkSomething(index, gSomeGlobalIndex)) {
                        return true;
                    }
                } else if (subType == 2) {
                    int index;
                    if (*(int*)(this + 0x54) == 0) {
                        index = 0;
                    } else {
                        index = *(int*)(this + 0x54) - 0x48;
                    }
                    // Compare ID fields at +0x1ed4 from the two objects
                    uint32_t ownId = *(uint32_t*)(index + 0x1ed4);
                    uint32_t otherId = *(uint32_t*)(*(int*)(this + 0x50) + 0x1ed4);
                    if (ownId == otherId) {
                        return true;
                    }
                }
            }
            break;

        default:
            // Fallback to base class handler for unknown events
            return defaultEventHandler(param2, param3, eventType, param5);
        }
        return false;
    }
};