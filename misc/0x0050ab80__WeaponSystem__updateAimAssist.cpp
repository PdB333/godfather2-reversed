// FUNC_NAME: WeaponSystem::updateAimAssist

#include <cstdint>

// Forward declarations
struct WeaponComponent; // size 0x50
struct CharacterState;
struct Entity;

// Global constants (from DAT_ refs)
extern float g_aimAssistRange; // DAT_00e2e780
extern float g_aimAssistTime; // DAT_00e44598
extern uint32_t g_someFrame; // DAT_00e2b1a4

// Helper functions (reconstructed names)
void unknownFunction(); // FUN_00414aa0
void quaternionNormalize(float* q); // FUN_0044d680
bool performRaycast(float* out, const float* quat, void* buf1, void* buf2, uint32_t extra, int param6, int param7); // FUN_004afee0
void fireWeapon(WeaponComponent* weapon); // FUN_00509590

class WeaponSystem {
public:
    // +0x24: Pointer to character state
    CharacterState* characterState;
    // +0xac: Array of target entity pointers (indexed by weapon offset +0x56)
    Entity** targetTable;

    // Weapon system likely has a pointer to weapon array
    WeaponComponent** weaponArrayPtr; // This is what param_1 points to

    // Method at 0x0050ab80
    uint32_t updateAimAssist(int weaponSlotIndex, const float* currentAimQuat, const float* targetQuat, float lerpFactor) {
        WeaponComponent* weaponArray = *weaponArrayPtr; // dereference param_1
        WeaponComponent* weapon = &weaponArray[weaponSlotIndex];

        // Read target index from weapon struct at +0x56 (ushort)
        uint16_t targetIndex = *(uint16_t*)((uint8_t*)weapon + 0x56);
        Entity* targetEntity = targetTable[targetIndex];

        // Check conditions: target valid, character state ready, and time condition
        if ((((*(uint8_t*)((uint8_t*)targetEntity + 0x48) & 1) != 0) &&
            (characterState != nullptr && *(int8_t*)((uint8_t*)characterState + 0x155) >= 0) &&
            (g_aimAssistTime < *reinterpret_cast<float*>(&lerpFactor))) { // in_XMM0_Da might be lerpFactor? Actually in_XMM0_Da is a float register passed as param5
            // Actually the comparison is with a float passed in XMM0, which is likely lerpFactor or some other value.
            // The decompiled code shows: DAT_00e44598 < in_XMM0_Da, and the function only receives param_5 as float.
            // So param_5 is that value.
            // Let's adjust: if (g_aimAssistTime < param_5) { ... }
        }

        // Original code more messy; let's rewrite based on decompiled logic:
        // iVar1 = base + param_2*0x50 + *param_1 -> weapon
        // uVar2 = targetEntity
        // Condition: (targetEntity->flags & 1) && characterState->someFlag >= 0 && g_aimAssistTime < param_5

        if ((((*(uint8_t*)((uint8_t*)targetEntity + 0x48) & 0x01) != 0) &&
            (characterState != nullptr && *(int8_t*)((uint8_t*)characterState + 0x155) >= 0) &&
            (g_aimAssistTime < *((float*)&param_5)))) { // param_5 is passed as float

            unknownFunction(); // FUN_00414aa0
            // local_34 = g_someFrame; (unused later)

            // Compute squared distance from weapon position (at weapon+0x30)
            float* pos = (float*)((uint8_t*)weapon + 0x30);
            float sqDist = pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2];
            bool isFar = (g_aimAssistRange < sqDist);

            // Copy target quaternion (param_4) to local
            float adjustedQuat[4];
            adjustedQuat[0] = targetQuat[0];
            adjustedQuat[1] = targetQuat[1];
            adjustedQuat[2] = targetQuat[2];
            adjustedQuat[3] = targetQuat[3];

            // Normalize the quaternion
            quaternionNormalize(adjustedQuat);

            if (isFar) {
                // Keep original aim quaternion (param_3)
                adjustedQuat[0] = currentAimQuat[0];
                adjustedQuat[1] = currentAimQuat[1];
                adjustedQuat[2] = currentAimQuat[2];
                adjustedQuat[3] = currentAimQuat[3];
            } else {
                // Interpolate: adjusted = param_5 * adjusted + param_3
                adjustedQuat[0] = lerpFactor * adjustedQuat[0] + currentAimQuat[0];
                adjustedQuat[1] = lerpFactor * adjustedQuat[1] + currentAimQuat[1];
                adjustedQuat[2] = lerpFactor * adjustedQuat[2] + currentAimQuat[2];
                adjustedQuat[3] = lerpFactor * adjustedQuat[3] + currentAimQuat[3];
            }

            // Prepare buffers for raycast
            float out[3]; // local_40? Actually local_40 is undefined1[12] but used as first param to raycast
            char buf1[28]; // local_20
            char buf2[16]; // local_30
            // actual call: FUN_004afee0(local_40, &local_50, local_20, local_30, *(undefined4*)(characterState + 0x114), 0, 0);
            uint32_t result = performRaycast((float*)out, adjustedQuat, buf1, buf2,
                                             *(uint32_t*)((uint8_t*)characterState + 0x114), 0, 0);
            if ((char)result != 0) {
                if (isFar) {
                    fireWeapon(weapon); // Probably fires the weapon
                }
                // Update target entity flags: clear bit0, set bit1
                *(uint32_t*)((uint8_t*)targetEntity + 0x48) = 
                    (*(uint32_t*)((uint8_t*)targetEntity + 0x48) & 0xFFFFFFFE) | 2;
                return (uint32_t)targetEntity; // uVar5
            }
        }
        return 0; // or original uVar5 & 0xffffff00
    }
};

// Note: The original decompiled code uses unaff_EDI as implicit this, 
// so this function is likely a method of WeaponSystem. 
// The param_1 (int*) is reinterpreted as &this->weaponArrayPtr. 
// The signature is adapted accordingly. The condition uses param_5 which is the float passed as 5th arg (originally param_5). 
// The in_XMM0_Da is that float. I've used param_5 directly.