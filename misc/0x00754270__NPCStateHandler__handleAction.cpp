// FUNC_NAME: NPCStateHandler::handleAction
// Function address: 0x00754270
// This function handles state transitions for an NPC (likely a state machine update).
// The switch cases correspond to action IDs (state IDs) ranging from 10 to 27.
// It calls various engine functions for animation, sound, effects, etc.

#include <cstdint>

// Assume these are known globals (float constants, vectors)
extern float _DAT_00d5cf70; // Threshold for some check
extern int DAT_00d5fb68; // Some global integer
extern float _DAT_00d64ba0; // Sound ID?
extern float _DAT_00d5c458; // Another sound ID?
extern float _DAT_00d64c68; // Some global float (e.g., a threshold)
extern float _DAT_00d64b90; // Reference vector (probably a direction)
extern float _DAT_00d64b98; // Another vector component
extern int _DAT_00d5ef90; // Some global parameter (maybe a shader constant)

class NPCStateHandler {
public:
    // Member offsets (inferred from decompiled code)
    // +0x00: vtable pointer (not stored)
    // +0x50? Actually param_1+0x14 -> m_character (some important object)
    // +0x60? param_1+0x18 -> m_actionParam (int)
    // +0x64? param_1+0x19 -> m_x, etc.
    // But we'll just use array indexing for simplicity.

    uint handleAction(int param2, int param3, int param4, int actionId, int param6);
};

// Forward declarations of called functions (with descriptive names)
void playSound(uint soundId);
void playAnimEvent(); // FUN_00752d10
int isRunSpeedCritical(); // FUN_00806440
void* getTrackToPositionStateTable(); // Actually returns a string/ID
void setAnimationState(int param2, int param3, void* stateTable);
void setFlagSomething(int flag);
int isPlayerAlive(); // FUN_006252f0
void doDialogSound(); // FUN_007f7e40
void playSoundWithParams(int soundId, float volume);
void somethingWithSounds(int a, int b, int c); // FUN_007fd950
void loadSomething(); // FUN_00753d80
void* getCameraTransform(int, int); // FUN_006fbc40
void setScreenEffect(int, int, void*, int); // FUN_007f96a0
void releaseCameraTransform(); // FUN_006fbc70
char isInputActive(int inputId); // FUN_00690150
void resetActionState(); // FUN_00753650
void setPlayerVisible(bool visible); // FUN_005512c0
void setVectorToZero(float* vec); // FUN_0046fe50
void playSoundAtLocation(int soundId); // FUN_007f63e0
int isWeaponReady(); // FUN_007f41e0
void fireWeapon(); // FUN_004abc20
void charTurnToTarget(); // FUN_00753780
void buildOrientationMatrix(float* outMatrix, float* direction, float* up, float* right); // FUN_004a0370
float* getMuzzleTransform(); // FUN_00471610
int checkGameplayFlag(uint32 flagHash); // probably hash "Active" = 0x369ac561
void startVFX(int vfxId); // FUN_007f9680
void stopVFX(int vfxId); // FUN_007f9690
void setShaderToggle(bool enable, int, int param); // FUN_007f4490
uint baseHandler(int param2, int param3, int param4, int actionId, int param6); // FUN_004ac700 (base class)

uint NPCStateHandler::handleAction(int param2, int param3, int param4, int actionId, int param6) {
    bool result = true; // local_7d = 1
    // Note: param_1 is 'this'
    int* thisPtr = reinterpret_cast<int*>(this); // For offset access

    switch (actionId - 10) {
    case 0: // actionId == 10
        // Store param2 into some member
        thisPtr[0x18] = param2; // m_actionParam
        playSound(0x33); // Some sound ID
        playAnimEvent();
        {
            // Check if run speed is critical and not interrupted
            int* character = reinterpret_cast<int*>(thisPtr[0x14]);
            float currentTime = (**(code**)(*character + 0xc0))(); // getAnimationTime?
            (**(code**)(*character + 0xc4))(); // something else?
            float threshold = (float)currentTime * _DAT_00d5cf70; // threshold calculation
            // Compare with something
            float someValue = (float)(int)currentTime; // likely this is actually the result of the function call
            if (threshold <= someValue &&
                ((*(uint*)(thisPtr[0x14] + 0x1b94) >> 0xf) & 1) == 0 &&
                isRunSpeedCritical() != 0) {
                // Set a bit flag at offset 0x1b94
                *(uint*)(thisPtr[0x14] + 0x1b94) |= 0x2000; // BIT13? Possibly "can run"
                return 1;
            }
        }
        break;

    case 1: // actionId == 11
        // Directly call a virtual function on this object with some arguments
        (**(code**)(*thisPtr + 0x2c))(0xa1be204, 1, 1, 0, DAT_00d5fb68, 0x3f800000);
        return (uint)DAT_00d5fb68 >> 0x18; // Return something

    case 2: // actionId == 12
        if ((thisPtr[0x1e] == 1) || (thisPtr[0x1e] == 2)) {
            // If certain internal state, set a new state table
            void* stateTable = getTrackToPositionStateTable(); // returns "trackToPositionAndDirectionStateTable"
            (**(code**)(*thisPtr + 0x20))(param2, param3, stateTable);
            setFlagSomething(1);
            return (uint)(reinterpret_cast<uint>(this) >> 0x18); // Warning: uninitialized register? Probably return something else
        }
        break;

    case 3: // actionId == 13
        if (isPlayerAlive() == 0) {
            doDialogSound();
            playSoundWithParams(6, _DAT_00d64ba0);
            return 1;
        }
        somethingWithSounds(6, 6, 10);
        playSoundWithParams(6, _DAT_00d5c458);
        return 1;

    case 4: // actionId == 14
        loadSomething();
        {
            void* cameraTransform = getCameraTransform(0, 0);
            setScreenEffect(0, 0, cameraTransform, 0);
            releaseCameraTransform();
            if (isInputActive(0x33) != 0) {
                resetActionState();
                playSound(0x33);
                return 1;
            }
        }
        break;

    case 5: // actionId == 15
        if (isPlayerAlive() == 0) {
            setPlayerVisible(1);
            return 1;
        }
        setPlayerVisible(0);
        return 1;

    case 6: // actionId == 16
        // Compare a global float with a weighted sum
        if (_DAT_00d64c68 < 
            (float)thisPtr[0x24] * (float)thisPtr[0x1a] + 
            (float)thisPtr[0x19] * (float)thisPtr[0x23] + 
            (float)thisPtr[0x25] * (float)thisPtr[0x1b]) {
            setVectorToZero(reinterpret_cast<float*>(thisPtr + 0x23));
            return 1;
        }
        break;

    case 7: // actionId == 17
        playSoundAtLocation(0x2a);
        if (isWeaponReady() != 0) {
            fireWeapon();
            return 1;
        }
        break;

    case 8: // actionId == 18
        resetActionState();
        return 1;

    case 9: // actionId == 19
        charTurnToTarget();
        return 1;

    case 10: // actionId == 20
        if (isPlayerAlive() == 0) {
            // Call a virtual function on the character object at offset 0x198
            (**(code**)(*(int*)thisPtr[0x14] + 0x198))();
            // Handle some pointer chain
            if ((thisPtr[0x27] != 0) && (thisPtr[0x27] != 0x48)) {
                if (thisPtr[0x27] == 0) {
                    (**(code**)(*(int*)0 + 0x198))(); // Warning: likely null pointer, should be conditional
                    return 1;
                }
                (**(code**)(*(int*)(thisPtr[0x27] - 0x48) + 0x198))();
                return 1;
            }
        } else {
            // Player is alive
            if ((thisPtr[0x27] != 0) && (thisPtr[0x27] != 0x48)) {
                int iVar5;
                if (thisPtr[0x27] == 0) {
                    iVar5 = 0;
                } else {
                    iVar5 = thisPtr[0x27] - 0x48;
                }
                (**(code**)(*(int*)thisPtr[0x14] + 0x2a0))(iVar5);
                if (thisPtr[0x27] == 0) {
                    (**(code**)(*(int*)0 + 0x2a0))(thisPtr[0x14]); // Again warning
                    return ...; // uninitialized register return
                }
                (**(code**)(*(int*)(thisPtr[0x27] - 0x48) + 0x2a0))(thisPtr[0x14]);
                return ...;
            }
        }
        break;

    case 0xb: // actionId == 21
        if (((*(byte*)(thisPtr + 0x29) & 1) == 0) {
            int* character = reinterpret_cast<int*>(thisPtr[0x14]);
            float currentTime = (**(code**)(*character + 0xc0))();
            (**(code**)(*character + 0xc4))();
            if (/* some condition */) break;
        }
        // Clear a bit at 0x1b94
        *(uint*)(thisPtr[0x14] + 0x1b94) &= 0xffffdfff; // clear bit 0x2000 (same as set in case 0)
        return 1;

    case 0xc: // actionId == 22
        playSound(0x36);
        return 1;

    case 0xd: // actionId == 23
        // Build orientation matrix and set to character
        {
            int local_64 = thisPtr[0x1b];
            uint64_t local_6c = *(uint64_t*)(thisPtr + 0x19); // Two vectors
            if (((uint)thisPtr[0x29] >> 1) & 1) {
                local_64 = thisPtr[0x25];
                local_6c = *(uint64_t*)(thisPtr + 0x23);
                thisPtr[0x29] &= ~2; // clear bit 1
            }
            // Build matrix from direction and reference
            buildOrientationMatrix(&local_78, &local_6c, &_DAT_00d64b90, _DAT_00e447e0);
            float* muzzleTransform = getMuzzleTransform();
            // Copy matrix
            float local_50[4];
            for (int i = 0; i < 16; i++) {
                local_50[i] = muzzleTransform[i];
            }
            // Modify orientation
            local_50[2] = fStack_74 * 0.0 - local_78;
            local_50[1] = local_78 * 0.0 - local_70 * 0.0;
            // Use globals for rest
            local_40 = _DAT_00d64b90;
            local_38 = _DAT_00d64b98;
            local_28 = local_70;
            // Set transform on character via virtual function
            (**(code**)(*character + 0x2c))(local_50);
            return (uint) bStack_81;
        }

    case 0xe: // actionId == 24
        if (checkGameplayFlag(0x369ac561) != 0 && (((uint)thisPtr[0x29] >> 3) & 1) == 0) {
            startVFX(3);
            playSoundAtLocation(0x4b);
            thisPtr[0x29] |= 8; // set bit 3
            return 1;
        }
        break;

    case 0xf: // actionId == 25
        if (checkGameplayFlag(0x369ac561) != 0 && (((uint)thisPtr[0x29] >> 3) & 1) != 0) {
            stopVFX();
            playSound(0x4b);
            thisPtr[0x29] &= ~8; // clear bit 3
            return 1;
        }
        break;

    case 0x10: // actionId == 26
        if ((((uint)thisPtr[0x29] >> 4) & 1) == 0) {
            setShaderToggle(1, 0, _DAT_00d5ef90);
            thisPtr[0x29] |= 0x10; // set bit 4
            return 1;
        }
        break;

    case 0x11: // actionId == 27
        if ((((uint)thisPtr[0x29] >> 4) & 1) != 0) {
            setShaderToggle(0, 0, _DAT_00d5ef90);
            thisPtr[0x29] &= ~0x10; // clear bit 4
            return 1;
        }
        break;

    default:
        result = (bool)baseHandler(param2, param3, param4, actionId, param6);
        break;
    }
    return (uint)result;
}