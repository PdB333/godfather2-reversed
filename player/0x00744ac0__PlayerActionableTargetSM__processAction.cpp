// FUNC_NAME: PlayerActionableTargetSM::processAction

// Address: 0x00744ac0
// Role: Processes player action commands for state machine transitions (car enter/exit, cover, etc.)

#include <cstdint>

typedef unsigned char undefined1;
typedef unsigned int uint;
typedef float float10; // Extended precision from FPU, treated as float

// Forward declarations for called functions (stubs - real implementation elsewhere)
extern void FUN_007347e0(); // getCurrentContext? 
extern bool FUN_007448b0(); // isPlayerInCar? (returns 1 if true)
extern void FUN_00744530(); // enterCar?
extern int FUN_00471610(); // getCameraTransform?
extern float FUN_009afe40(); // getRandomFloat?
extern void FUN_0075e480(void* vec3, int flags); // updateCameraTarget?
extern bool FUN_0045f1b0(int characterID); // isCharacterAlive?
extern int FUN_0072f960(); // getCurrentCharacter?
extern void FUN_00744710(); // resetDriving?
extern void FUN_009afe00(); // initSomething?
extern void FUN_009b0620(float* vec3); // clearVelocity?
extern void FUN_007447a0(undefined4 param); // enterCover?
extern void FUN_009afea0(); // playAnimation?
extern undefined1 FUN_0075e390(undefined4, undefined4, undefined4, undefined4, undefined4); // defaultActionHandler

// Global constants (from game data)
extern float _DAT_00d577a0; // e.g., groundHeight
extern float _DAT_00d5780c; // e.g., fallSpeed
extern float DAT_00d5ccf8;  // e.g., defaultZOffset

// Assuming this class has the following fields (offset from this pointer):
// +0x00: vtable
// +0x2a: uint32 flags (bit 0: inCar, bit 1: climbing?)
// +0x30: ? (0x0c * 4 = 48 bytes? Offset to position maybe)
// +0x3d: float velocityX
// +0x3e: float velocityY
// +0x3f: float velocityZ (3 floats at +0x3d)
// +0x42: pointer to some character struct? (used as base for +0x4c bitfield)
// +0x44: int32 characterID or index

class PlayerActionableTargetSM {
public:
    // vtable +0x2c virtual method? setCameraFOV? (takes: unknown, int, int, int, float, float)
    typedef void (__thiscall* VCamFunc)(void*, undefined4, int, int, float, float);
    
    // Process an action command
    undefined1 processAction(undefined4 actionData2, undefined4 actionData3, undefined4 actionData4,
                             uint actionId, undefined4 actionData6)
    {
        float fVar1;
        uint3 uVar2; // packed flags from comparison
        char cVar3;
        undefined4 uVar4;
        int iVar5;
        uint uBitField;
        float10 randomVal; // extended precision
        undefined1 retVal = 1; // default success
        
        switch (actionId) {
        case 0x0e: // EXIT_VEHICLE? (14)
            uVar4 = FUN_007347e0(); // getPlayerVehicle?
            retVal = 0;
            // Call vtable+0x2c to set camera FOV? (last two floats 1.0)
            ((VCamFunc)(*(uint32*)this + 0x2c))(uVar4, 1, 0, 1, 1.0f, 1.0f);
            return retVal;
            
        case 0x0f: // ENTER_VEHICLE? (15)
            cVar3 = FUN_007448b0(); // isPlayerInCar?
            if (cVar3 != 0) {
                FUN_00744530(); // enterCar transition
                iVar5 = FUN_00471610(); // get camera transform pointer
                randomVal = (float10)FUN_009afe40(); // random factor
                
                fVar1 = (float)this->m_positionZ; // +0x0c (offset maybe in feet)
                // Compare with global ground height, build conditional flags
                uVar2 = CONCAT21(extraout_var,
                                 (fVar1 == _DAT_00d577a0) << 6 | 
                                 (NAN(fVar1) || NAN(_DAT_00d577a0)) << 2 | 
                                 2U | (fVar1 < _DAT_00d577a0));
                
                float local_vec[3]; // local_c, local_8, local_4
                local_vec[0] = (float)(randomVal * (float10)this->m_velocityX + (float10)*(float*)(iVar5 + 0x30));
                local_vec[1] = (float)(randomVal * (float10)this->m_velocityY + (float10)*(float*)(iVar5 + 0x34));
                local_vec[2] = (float)(randomVal * (float10)this->m_velocityZ + (float10)*(float*)(iVar5 + 0x38));
                
                // Determine flag based on ground comparison
                int flag;
                if (fVar1 == _DAT_00d577a0) {
                    flag = CONCAT31(uVar2, 1); // likely negative? 
                } else {
                    flag = (uint32)uVar2 << 8; // shifted
                }
                FUN_0075e480(local_vec, flag); // update camera position with offset
                return 1;
            }
            // If not in car, try to enter from ground
            iVar5 = this->m_characterID; // +0x44
            undefined4 param3 = _DAT_00d5780c; // fallback value
            cVar3 = FUN_0045f1b0(iVar5); // is character alive?
            if (cVar3 == 0) {
                iVar5 = FUN_0072f960(); // get some other character?
                param3 = DAT_00d5ccf8;  // default offset
            }
            retVal = 0;
            // Call vtable+0x2c (set camera)
            ((VCamFunc)(*(uint32*)this + 0x2c))(iVar5, 1, 0, 1, param3, 1.0f);
            return retVal;
            
        case 0x10: // COVER_ENTER? (16)
            FUN_00744710(); // reset some state
            return 1;
            
        case 0x11: // COVER_EXIT? (17)
            FUN_009afe00(); // init velocity?
            FUN_009b0620(&this->m_velocityX); // clear velocity vector (three floats)
            // Check bit 4 of character flags at +0x4c (from pointer at +0x42)
            uBitField = *(uint32*)(this->m_pCharacter + 0x4c) >> 4;
            if (((uBitField & 1) == 0) && (cVar3 = FUN_007448b0(), cVar3 == 0)) {
                goto commonEnter;
            }
            cVar3 = FUN_007448b0();
            if ((cVar3 != 0) && ((uBitField & 1) != 0)) {
                // Clear bit 0 of flags
                this->m_flags &= 0xfffffffe; // +0x2a
                return 1;
            }
            break; // fallthrough to default? Actually break from switch, return local_d = 1
            
        case 0x12: // ACTION_CLIMB? (18)
            cVar3 = FUN_007448b0();
            if (cVar3 == 0) {
                FUN_007447a0(actionData3); // start climb
                return 1;
            }
            break;
            
        case 0x13: // ACTION_JUMP? (19)
            cVar3 = FUN_007448b0();
            if ((cVar3 == 0) && (_DAT_00d577a0 < (float)this->m_positionZ)) {
                FUN_007447a0(actionData3); // jump action
                return 1;
            }
            break;
            
        case 0x14: // ACTION_ENTER_COVER? (20)
            FUN_009b0620(&this->m_velocityX); // clear velocity
            if ((*(uint32*)(this->m_pCharacter + 0x4c) >> 4 & 1) == 0) {
                goto commonEnter;
            }
            break;
            
        case 0x15: // ACTION_PLAY_ANIM? (21)
            FUN_009afea0(); // play some animation
            return 1;
            
        default:
            retVal = FUN_0075e390(actionData2, actionData3, actionData4, actionId, actionData6);
            return retVal;
        }
        
        // Common path for cases 0x11 and 0x14 when condition met
    commonEnter:
        this->m_flags |= 3; // +0x2a: set bits 0 and 1 (inCar or climbing)
        FUN_00744530(); // transition to driving/climbing state
        return 1;
    }

private:
    // Unknown fields, only those referenced are named:
    // Offset 0x00: void* vtable
    // Offset 0x2a: uint32 m_flags
    // Offset 0x0c: float m_positionZ (probably z coordinate)
    // Offset 0x3d: float m_velocityX
    // Offset 0x3e: float m_velocityY
    // Offset 0x3f: float m_velocityZ
    // Offset 0x42: char* m_pCharacter (pointer to character with flags at +0x4c)
    // Offset 0x44: int32 m_characterID
} __attribute__((packed)); // structure alignment unknown, but likely 4-byte aligned

// End of function