// FUNC_NAME: PlayerActionableTargetSM::handleAction
// Address: 0x0075c820
// This function handles action events for the player's actionable target state machine.
// Switches on actionType (param_5) with cases 10-15 (since case param_5 - 10).
// Uses offsets: +0x58 (animation/timer sub-state), +0x70+0x74 (some float pair),
// +0x78 (threshold), +0x80 (flags), +0x84 (accumulator), +0x9c (current state),
// +0xb8/+0xc0 (pointers to other objects like AI components).

#include <cstdint>

// Forward declarations of called functions
bool FUN_0075bd60(void* subState, int param); // e.g., startTimer
bool FUN_0075eb90(void* subState);            // e.g., triggerTransition
bool FUN_0075b840();                          // some condition check
bool FUN_0075c580();                          // another condition
void FUN_00742a70(int state);                 // e.g., setState
void FUN_0074a210(int state);                 // e.g., applyAction
void FUN_004daf90(void* ptr);                 // likely deleteObject
int FUN_00624bd0(uint32_t hash);              // find object by hash (0x6862a74c)
bool FUN_00718130();                          // some global flag check
bool FUN_0054f220(int param);                 // e.g., isActionAllowed (0xFA)
void FUN_00744610(bool flag);                 // set something
void FUN_00508f40(uint32_t bits, bool value); // set flag bits

// Default handler for other action types (likely base class)
uint8_t FUN_004ac700(int param2, float param3, uint32_t param4, int param5, uint32_t param6);

uint8_t __thiscall PlayerActionableTargetSM::handleAction(void* thisPtr, int param2, float param3, uint32_t param4, int actionType, uint32_t param6)
{
    float fVar1;
    uint32_t uVar2;
    uint8_t uVar5 = 1; // default success return
    int iVar6, iVar7;

    uVar2 = DAT_00d5ccf8; // some global constant (likely 0 or from context)

    switch(actionType - 10) {
        case 0: // action == 10
            // Store a float pair (maybe direction or rotation)
            *(uint32_t*)(thisPtr + 0x70) = DAT_00d5ccf8;
            *(uint32_t*)(thisPtr + 0x74) = uVar2;
            // Check current state (offset 0x9c) is not zero and not 0x48, and flag bit 8 is clear
            if ( (*(int*)(thisPtr + 0x9c) != 0) && (*(int*)(thisPtr + 0x9c) != 0x48) &&
                 ((*(uint32_t*)(thisPtr + 0x80) >> 8 & 1) == 0) ) {
                // Convert state to a derived index (subtract 0x48)
                iVar7 = (*(int*)(thisPtr + 0x9c) == 0) ? 0 : (*(int*)(thisPtr + 0x9c) - 0x48);
                FUN_00742a70(iVar7); // set state
                *(uint32_t*)(thisPtr + 0x80) |= 0x80; // set flag bit 7
                return 1;
            }
            break;

        case 1: // action == 11
            fVar1 = (float)param2;
            *(uint32_t*)(thisPtr + 0x80) &= 0xffffffbf; // clear flag bit 6
            if (param2 < 0) {
                fVar1 += DAT_00e44578; // constant (likely 1.0f for rounding)
            }
            *(float*)(thisPtr + 0x74) = fVar1 * DAT_00d5efb8; // scale by global
            FUN_0075bd60(thisPtr + 0x58, 0); // start timer of type 0
            return 1;

        case 2: // action == 12
            // Convert state again
            iVar7 = (*(int*)(thisPtr + 0x9c) == 0) ? 0 : (*(int*)(thisPtr + 0x9c) - 0x48);
            // Look up a specific object by hash (probably a gameplay manager)
            iVar6 = FUN_00624bd0(0x6862a74c); 
            if (iVar6 != 0) {
                uint8_t cVar3 = FUN_00718130(); // check global condition
                if (cVar3 == 0) {
                    // If condition false, free pointer at offset 0xc0 of that object
                    if (*(int*)(iVar6 + 0xc0) != 0) {
                        FUN_004daf90((uint32_t*)(iVar6 + 0xc0));
                        *(uint32_t*)(iVar6 + 0xc0) = 0;
                    }
                } else {
                    FUN_0074a210(iVar7); // apply something to current state
                }
            }
            // Check if action 0xFA is allowed
            uint8_t cVar3 = FUN_0054f220(0xFA);
            if (cVar3 == 0) {
                param3 = 0.0f;
            } else {
                param3 += *(float*)(thisPtr + 0x84); // accumulate
            }
            *(float*)(thisPtr + 0x84) = param3;
            fVar1 = (float)param2;
            if (param2 < 0) {
                fVar1 += DAT_00e44578;
            }
            // Check if scaled difference exceeds current value at +0x74
            if (fVar1 * DAT_00d5efb8 - *(float*)(thisPtr + 0x74) > 1.0f) {
                uint8_t cVar3 = FUN_0075c580(); // additional condition
                if (cVar3 == 0) {
                    *(uint32_t*)(thisPtr + 0x80) &= 0xffffffbf; // clear flag bit 6
                    return 1;
                }
                *(uint32_t*)(thisPtr + 0x80) |= 0x40; // set flag bit 6
                // Check if objects at +0xc0 and +0xb8 are valid and not equal to 0x50
                if ( (*(int*)(thisPtr + 0xc0) != 0) && (*(int*)(thisPtr + 0xc0) != 0x50) ) {
                    iVar7 = FUN_00757a50(); // get some related object
                    if (iVar7 != 0) {
                        FUN_005f7ba0(iVar7); // trigger something on that object
                        return 1;
                    }
                }
            }
            break;

        case 3: // action == 13
            fVar1 = (float)param2;
            *(uint32_t*)(thisPtr + 0x80) &= 0xffffffbf; // clear flag bit 6
            if (param2 < 0) {
                fVar1 += DAT_00e44578;
            }
            *(float*)(thisPtr + 0x74) = fVar1 * DAT_00d5efb8;
            FUN_0075bd60(thisPtr + 0x58, 1); // start timer of type 1
            return 1;

        case 4: // action == 14
            fVar1 = (float)param2;
            if (param2 < 0) {
                fVar1 += DAT_00e44578;
            }
            // Compare scaled difference with threshold at +0x78
            if (*(float*)(thisPtr + 0x78) < fVar1 * DAT_00d5efb8 - *(float*)(thisPtr + 0x74)) {
                iVar7 = thisPtr + 0x58;
                *(float*)(thisPtr + 0x74) = fVar1 * DAT_00d5efb8;
                FUN_0075bd60(iVar7, 1); // restart timer type 1
                // Depending on pointer at +0xb8, choose transition call
                if (*(int*)(thisPtr + 0xb8) == 0) {
                    FUN_0075eb90(iVar7); // start sequence A
                } else {
                    FUN_0075eb90(iVar7); // start sequence B (identical in this build)
                }
                return 1;
            }
            break;

        case 5: // action == 15
            uint8_t bVar4 = FUN_0075b840(); // condition check
            // Compare with current flag bit 9
            if (bVar4 != ((*(uint32_t*)(thisPtr + 0x80) >> 9) & 1)) {
                // If either pointer at +0xb8 or +0xc0 is valid and not 0x50
                if ( ( (*(int*)(thisPtr + 0xb8) != 0) && (*(int*)(thisPtr + 0xb8) != 0x50) ) ||
                     ( (*(int*)(thisPtr + 0xc0) != 0) && (*(int*)(thisPtr + 0xc0) != 0x50) ) ) {
                    FUN_00744610(bVar4); // set something based on condition
                }
                FUN_00508f40(0x200, bVar4); // set flag bit 9 in some global?
                return 1;
            }
            break;

        default:
            uVar5 = FUN_004ac700(param2, param3, param4, actionType, param6);
    }
    return uVar5;
}