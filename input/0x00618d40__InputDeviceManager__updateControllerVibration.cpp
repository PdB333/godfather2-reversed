// FUNC_NAME: InputDeviceManager::updateControllerVibration
// Address: 0x00618d40
// Role: Updates force feedback (vibration) for a given controller slot based on current effect data.

#include <cstdint>

// Forward declarations
class ForceFeedbackManager; // Object at g_pForceFeedbackManager
class AudioManager;         // Object at g_pAudioManager

// Global pointers (inferred)
extern ForceFeedbackManager* g_pForceFeedbackManager;   // DAT_01205750
extern AudioManager* g_pAudioManager;                   // DAT_0120595c

// Size 0x38 per entry
struct ForceFeedbackEffect {
    uint8_t padding0[0x14];
    uint32_t effectParam;          // +0x14  (duration or intensity, sent to audio)
    uint8_t padding18[0x8];
    uint8_t motorLeft;             // +0x20  (left motor amplitude)
    uint8_t motorRight;            // +0x21
    uint8_t motorCenter;           // +0x22
    uint8_t motorUnknown;          // +0x23
    uint8_t motorAll;              // +0x24  (sets all motors? used with IDs 1,2,3)
    uint8_t padding26[0x2];
    uint32_t motorIntensity;       // +0x28  (additional intensity value)
};

// Global effect table (size 0x38 per entry)
extern ForceFeedbackEffect g_forceFeedbackTable[]; // DAT_011a0f28

// Per-slot cached vibration bytes and int (0xC bytes per slot, max 16+)
extern uint8_t g_cachedMotorLeft[16*12];   // DAT_011f7450  (offsets 0,1,2 for left,right,center)
extern uint8_t g_cachedMotorCenter[16*12]; // Actually aliased? The code uses iVar2 as index.
// The above is an approximation; the code accesses a flat byte array: (&DAT_011f7450)[iVar2] etc.
// We'll model as a struct per slot:
struct SlotVibrationCache {
    uint8_t left;       // +0x0
    uint8_t right;      // +0x1
    uint8_t center;     // +0x2
    uint8_t unknown1;   // +0x3  (from offset 0x23)
    uint8_t allMotors;  // +0x4  (from offset 0x24)
    uint8_t pad[3];
    uint32_t intensity; // +0x8  (from offset 0x28)
};
extern SlotVibrationCache g_slotVibrationCache[]; // DAT_011f7450

// Forward declaration
bool isControllerVibrationEnabled(); // FUN_00618c40

// The function
void __fastcall InputDeviceManager::updateControllerVibration(uint32_t slotIndex) {
    uint32_t adjustedSlot = slotIndex;
    // Map slots >15 to a different range (for network players? 0xF1 + slot)
    if (slotIndex > 15) {
        adjustedSlot = slotIndex + 0xF1;
    }

    // The 'this' pointer is passed in EAX (implicit). But the function is not a member?
    // In the decompiler, in_EAX is an extra parameter via register.
    // It likely points to the global controller state or is a static function.
    // We'll treat it as a static function using the global effect table pointer.
    ForceFeedbackEffect* pEffect = nullptr;
    
    // Check if a global effect pointer is valid (in_EAX)
    // In the original, in_EAX comes from a global or a previous call.
    // We'll assume there is a global current effect pointer.
    static ForceFeedbackEffect* g_pCurrentEffect = nullptr; // in_EAX
    if (g_pCurrentEffect == nullptr) {
        goto setDefaultEffect;
    }
    
    uint32_t effectIndex = *(uint32_t*)((uint8_t*)g_pCurrentEffect + 0x1C);
    if (effectIndex != 0) {
        if (effectIndex > 0xFFF) {
            goto setDefaultEffect;
        }
        pEffect = &g_forceFeedbackTable[effectIndex];
    } else {
        pEffect = g_pCurrentEffect; // Use the pointer directly if index is 0?
    }
    
    if (pEffect == nullptr) {
        goto setDefaultEffect;
    }
    
    // Check if vibration is allowed
    if (!isControllerVibrationEnabled()) {
        // Still update non-motor fields (center, motorAll, intensity) even if disabled?
        // The decompiler shows that if check passes, it updates left/right/center; then after the if, it always updates the rest.
        // So we need to replicate the logic.
    }
    
    // Only update if vibration is enabled (cVar3 == 0)
    // Note: The decompiled code shows: if (cVar3 == '\\0') then update left/right/center.
    bool vibrationEnabled = isControllerVibrationEnabled(); // returns 0 = enabled
    if (!vibrationEnabled) {
        // Compare and update left motor (ID 7)
        if (g_slotVibrationCache[slotIndex].left != pEffect->motorLeft) {
            g_pForceFeedbackManager->setMotor(adjustedSlot, 7, pEffect->motorLeft); // vtable+0x114
            g_slotVibrationCache[slotIndex].left = pEffect->motorLeft;
        }
        // Right motor (ID 6)
        if (g_slotVibrationCache[slotIndex].right != pEffect->motorRight) {
            g_pForceFeedbackManager->setMotor(adjustedSlot, 6, pEffect->motorRight);
            g_slotVibrationCache[slotIndex].right = pEffect->motorRight;
        }
        // Center motor (ID 5)
        if (g_slotVibrationCache[slotIndex].center != pEffect->motorCenter) {
            g_pForceFeedbackManager->setMotor(adjustedSlot, 5, pEffect->motorCenter);
            g_slotVibrationCache[slotIndex].center = pEffect->motorCenter;
        }
    }
    
    // Always update these (outside the if)
    // Unknown motor (ID 10) from offset 0x23
    if (g_slotVibrationCache[slotIndex].unknown1 != pEffect->motorUnknown) {
        g_pForceFeedbackManager->setMotor(adjustedSlot, 10, pEffect->motorUnknown);
        g_slotVibrationCache[slotIndex].unknown1 = pEffect->motorUnknown;
    }
    
    // All motors (IDs 1,2,3) from offset 0x24
    if (g_slotVibrationCache[slotIndex].allMotors != pEffect->motorAll) {
        g_pForceFeedbackManager->setMotor(adjustedSlot, 1, pEffect->motorAll);
        g_pForceFeedbackManager->setMotor(adjustedSlot, 2, pEffect->motorAll);
        g_pForceFeedbackManager->setMotor(adjustedSlot, 3, pEffect->motorAll);
        g_slotVibrationCache[slotIndex].allMotors = pEffect->motorAll;
    }
    
    // Intensity value (ID 4) from offset 0x28
    if (g_slotVibrationCache[slotIndex].intensity != pEffect->motorIntensity) {
        g_pForceFeedbackManager->setMotor(adjustedSlot, 4, pEffect->motorIntensity);
        g_slotVibrationCache[slotIndex].intensity = pEffect->motorIntensity;
    }
    
    // Finally, call audio manager with effect param (offset 0x14)
    g_pAudioManager->setEffect(adjustedSlot, pEffect->effectParam); // vtable+0x104
    return;
    
setDefaultEffect:
    // If no valid effect, set default (zero)
    g_pAudioManager->setEffect(adjustedSlot, 0);
    return;
}