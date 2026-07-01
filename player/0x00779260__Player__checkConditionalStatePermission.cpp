// FUNC_NAME: Player::checkConditionalStatePermission

#include <cstdint>

// Player class (EARS::Player) - core player entity state machine condition checker
// member offsets:
// +0x00 vtable
// +0x20 some object pointer (maybe current weapon?)
// +0x30 float field (health? timer?)
// +0x5c pointer to some system (probably SimManager or EntityDataManager)
// +0x88 current state/type ID (0 = normal, 0x48 = death/cinematic?)
// +0x90 bitfield flags (state condition flags)
// +0xac some timestamp/cooldown counter

class Player {
public:
    // Returns true if the given condition (param_4 - 0x12) is allowed for the player
    // Conditions: 0 = canDie, 1 = canShoot, 2 = canMove, 3 = isCrouching, 4 = isInVehicle,
    // 5 = canUseCover, 7 = isRunning, 8 = isInCombat, 9 = isAiming, 10 = canUseGadget
    uint8_t checkConditionalStatePermission(uint32_t param2, uint32_t param3, int32_t conditionId, uint32_t param5) {
        uint8_t result = 0;
        
        switch (conditionId - 0x12) {
        case 0: // canDie?
            if (this->stateType == 0) { // normal state
                return true;
            }
            return this->stateType == 0x48; // death/cinematic state
        case 1: // canShoot?
            // Check if shooting is allowed via some global flag (bit 13 of +0x1f58)
            if (!(*(uint32_t*)(this->someSystemPtr + 0x1f58) >> 0xd & 1)) {
                return false;
            }
            // Must not be holding something (weapon? tool?) at +0x20
            if (this->heldObjectPtr != 0) {
                return false;
            }
            return true;
        case 2: // canMove?
            result = externalCanMoveCheck(); // FUN_00778a30
            return result;
        case 3: // isCrouching?
            return (this->stateFlags >> 4) & 1;
        case 4: // isInVehicle?
            if (this->someFloatField <= globalVehicleThreshold) {
                return false;
            }
            return true;
        case 5: // canUseCover?
            // Complex condition checking cover state availability
            if ((this->stateType != 0) && (this->stateType != 0x48)) {
                int32_t basePtr = (this->stateType == 0) ? 0 : (this->stateType - 0x48);
                uint32_t* coverData = (uint32_t*)(basePtr + 0xc88);
                
                // Check bit 2 (cover flag)
                if (!((*coverData >> 2) & 1)) {
                    // Check bit 1 of state flags
                    if (!((this->stateFlags >> 1) & 1)) {
                        // Check some external condition
                        uint8_t extResult = externalCoverConditionCheck(); // FUN_00778f80
                        if (extResult == 0 || !((this->stateFlags >> 2) & 1)) {
                            // Check bit 11
                            uint32_t* coverData2 = (uint32_t*)(basePtr + 0xc88);
                            if (!((*coverData2 >> 0xb) & 1)) {
                                // Check bit 14
                                uint32_t* aimData = (uint32_t*)(basePtr + 0xf28);
                                if (!((*aimData >> 0xe) & 1)) {
                                    // Check bit 12
                                    uint32_t* aimData2 = (uint32_t*)(basePtr + 0xf28);
                                    if (!((*aimData2 >> 0xc) & 1)) {
                                        // Check external camera/aim condition
                                        uint8_t camResult = externalAimConditionCheck(); // FUN_0087cb30
                                        if (camResult == 0) {
                                            // Check bit 5 of state flags
                                            if (!((this->stateFlags >> 5) & 1)) {
                                                // Check current weapon/action type
                                                int32_t currentAction = getCurrentActionType(); // FUN_0077dd80
                                                int32_t expectedAction = *(int32_t*)(this->someSystemPtr + 0x2580);
                                                if (currentAction != expectedAction && currentAction == 3) {
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        default:
            result = defaultConditionCheck(param2, param3, conditionId, param5);
            break;
        case 7: // isRunning?
            if (globalRunThreshold < this->someFloatField) {
                int32_t action = getCurrentActionType(); // FUN_0077dd80
                if (action != 3) {
                    return true;
                }
            }
            break;
        case 8: // isInCombat?
            return (this->stateFlags >> 5) & 1;
        case 9: // isAiming?
            return (this->stateFlags >> 6) & 1;
        case 10: // canUseGadget?
            if ((this->stateType != 0) && (this->stateType != 0x48)) {
                if (!((this->stateFlags >> 3) & 1)) {
                    int32_t basePtr2 = (this->stateType == 0) ? 0 : (this->stateType - 0x48);
                    // Check bit 2
                    uint32_t* data1 = (uint32_t*)(basePtr2 + 0xc88);
                    if (!((*data1 >> 2) & 1)) {
                        // Check bit 11
                        uint32_t* data2 = (uint32_t*)(basePtr2 + 0xc88);
                        if (!((*data2 >> 0xb) & 1)) {
                            // Check bit 14
                            uint32_t* data3 = (uint32_t*)(basePtr2 + 0xf28);
                            if (!((*data3 >> 0xe) & 1)) {
                                // Check bit 12
                                uint32_t* data4 = (uint32_t*)(basePtr2 + 0xf28);
                                if (!((*data4 >> 0xc) & 1)) {
                                    uint8_t camCheck = externalAimConditionCheck(); // FUN_0087cb30
                                    if (camCheck == 0) {
                                        // Check cooldown timer
                                        return (uint32_t)(globalCooldownTimer - this->gadgetCooldownTimestamp) < 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return result;
    }

private:
    // Member variables (offsets from this)
    uint32_t* vtable;                                           // +0x00
    uint32_t pad04_1c[7];                                       // +0x04..+0x1c
    int32_t heldObjectPtr;                                      // +0x20 (weapon/item currently held)
    uint32_t pad24_0c[3];                                       // +0x24..+0x2c
    float someFloatField;                                       // +0x30 (health, stamina, or vehicle detection?)
    uint32_t pad34_28[10];                                      // +0x34..+0x58
    int32_t someSystemPtr;                                      // +0x5c (SimManager/EntityDataManager?)
    uint32_t pad60_28[10];                                      // +0x60..+0x84
    int32_t stateType;                                          // +0x88 (0=normal, 0x48=special)
    uint32_t pad8c_4;                                           // +0x8c
    uint32_t stateFlags;                                        // +0x90 (bitfield for various states)
    uint32_t pad94_18[6];                                       // +0x94..+0xa8
    int32_t gadgetCooldownTimestamp;                            // +0xac (timestamp for gadget cooldown)
    
    // External function declarations (stubs)
    uint8_t externalCanMoveCheck();                             // FUN_00778a30
    uint8_t externalCoverConditionCheck();                      // FUN_00778f80
    uint8_t externalAimConditionCheck();                        // FUN_0087cb30
    int32_t getCurrentActionType();                             // FUN_0077dd80
    uint8_t defaultConditionCheck(uint32_t, uint32_t, int32_t, uint32_t); // FUN_0073e300
};

// Global variables
extern float globalVehicleThreshold;                            // _DAT_00d68354
extern float globalRunThreshold;                                // _DAT_00d68358
extern int32_t globalCooldownTimer;                             // DAT_0120521c