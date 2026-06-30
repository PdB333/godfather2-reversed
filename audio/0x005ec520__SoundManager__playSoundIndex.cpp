// FUNC_NAME: SoundManager::playSoundIndex
// Address: 0x005ec520
// Role: Plays a sound from a pre-loaded sound index (0-127). Handles state checks and parameter setting.

#include <cstdint>

// Forward declarations of called functions (from audio system)
extern bool isSoundReady(void* soundHandle); // FUN_00c9eb10
extern void lockAudio();                      // FUN_00c9eac0
extern void unlockAudio();                    // FUN_00c9eae0
extern void* getAudioSettings();              // FUN_005e9d10
extern void setSoundParameter(void* audioSystem, void* busOrGroup, int parameterIndex, float* value); // FUN_00c9cbe0
extern void setParameterValue(int parameterIndex, float* value); // FUN_00c9cd40
extern float g_sentinelValue;                 // DAT_00e2b05c

// Sound entry structure (size 0xf8 = 248 bytes)
struct SoundSlot {
    uint8_t pad_bc[0xbc];          // padding to offset +0xbc
    void* soundData;               // +0xbc: pointer to sound data (non-null if assigned)
    uint8_t pad_dc[0xdc - 0xbc - 4]; // padding
    void* soundHandle1;            // +0xdc: primary sound handle
    void* soundHandle2;            // +0xe0: secondary sound handle (crossfade)
    float soundParameter;          // +0xe4: parameter value (e.g., volume/pitch)
};

// Main class (SoundManager)
class SoundManager {
public:
    // Assuming this class has at least:
    void* audioSystem;             // +0x580: pointer to audio system (e.g., FMOD)
    SoundSlot slots[128];          // +0x5a0: array of 128 sound slots (0xf8 each)

    // Note: The function also reads registers EBX and EDI at entry, likely set by caller.
    // EBX probably points to a global context (e.g., AudioManager instance or sound bus).
    // EDI may contain a return value from a previous call (e.g., high byte of a float).
    // We'll treat them as implicit parameters (register) for reconstruction.
    uint8_t playSoundIndex(uint16_t soundIndex);
};

uint8_t SoundManager::playSoundIndex(uint16_t soundIndex) {
    // Registers passed by caller (Ghidra's unaff_EBX, unaff_EDI)
    void* ebxPtr;          // unaff_EBX (assumed pointer to something)
    uint32_t ediVal;       // unaff_EDI (raw value)
    uint8_t ediHighByte = (uint8_t)(ediVal >> 0x18); // top byte of EDI (used as return value in some path)

    uint8_t result = 1; // uVar3 (default return value for failure branch)

    if ((soundIndex < 0x80) && (audioSystem != nullptr)) {
        SoundSlot* slot = &slots[soundIndex];
        if ((slot->soundData != nullptr) && (slot->soundHandle1 != nullptr)) {
            char isReady = isSoundReady(slot->soundHandle1);
            if (isReady != 0) {
                if (slot->soundHandle2 != nullptr) {
                    isSoundReady(slot->soundHandle2); // check secondary handle readiness
                }
                lockAudio();

                void* settings = getAudioSettings(); // returns some settings object
                // Set sound parameter index 2 (e.g., pitch or volume) with current parameter value
                setSoundParameter(audioSystem, *(void**)((uint8_t*)settings + 0x10), 2, &slot->soundParameter);
                float tempValue = slot->soundParameter; // local copy
                setParameterValue(2, &tempValue);

                // Check for early return condition:
                // - tempValue equals a sentinel value (e.g., -1.0f)
                // - a byte at ebxPtr+0x47 is not 2
                // - a local char (cStack_4) is zero (likely uninitialized; maybe a debug flag)
                char localFlag; // cStack_4 (uninitialized, but used in condition)
                if ((tempValue == g_sentinelValue) &&
                    (*(uint8_t*)((uint8_t*)ebxPtr + 0x47) != 2) &&
                    (localFlag == 0)) {
                    unlockAudio();
                    return 0; // early exit without cleaning slot
                }

                // Normal path: finalize and clear slot
                setParameterValue(1, nullptr); // set parameter 1 to default
                slot->soundHandle1 = nullptr;
                slot->soundHandle2 = nullptr;
                slot->soundParameter = 0.0f;
                unlockAudio();
                return ediHighByte; // return the high byte of EDI (possibly status)
            }
            result = 0; // sound not ready
        }
    }
    return result;
}