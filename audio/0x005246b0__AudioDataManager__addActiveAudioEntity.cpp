// FUNC_NAME: AudioDataManager::addActiveAudioEntity
// Address: 0x005246b0
// Reconstructed C++ from Ghidra decompilation
// Registers an audio entity for active processing (up to 24 simultaneous sources)
#include <cmath>

class AudioDataManager {
public:
    static const int MAX_ACTIVE_AUDIO = 24;
    static int s_activeAudioCount;                        // DAT_01194d00
    static void* s_activeAudioPointers[MAX_ACTIVE_AUDIO]; // DAT_01197d10
    static float s_activeAudioPosX[MAX_ACTIVE_AUDIO];     // DAT_01194b80
    static float s_activeAudioPosY[MAX_ACTIVE_AUDIO];     // DAT_01194b84
    static float s_activeAudioPosZ[MAX_ACTIVE_AUDIO];     // DAT_01194b88
    static float s_activeAudioParam[MAX_ACTIVE_AUDIO];    // DAT_01194b8c (magnitude/parameter)

    // External global constants (defined elsewhere)
    extern const float g_audioGlobalFactor;  // DAT_00e44718
    extern const float g_audioSpeedFactor;   // DAT_00e2cd54

    // Register an audio entity for active processing
    // @param entity: pointer to an audio entity (likely EARS audio source)
    static void addActiveAudioEntity(void* entity) {
        if (entity == nullptr) return;

        int count = s_activeAudioCount;

        // Entity must not already have bits 1 or 2 set in flags at +0x460
        if ((*(uint8_t*)((uintptr_t)entity + 0x460) & 6) != 0) return;
        // Global list must not be full
        if (count >= MAX_ACTIVE_AUDIO) return;
        // Entity must be marked active at +0x451
        if (*(uint8_t*)((uintptr_t)entity + 0x451) == 0) return;

        // Store entity pointer
        s_activeAudioPointers[count] = entity;

        // Retrieve entity fields
        float entitySpeed = *(float*)((uintptr_t)entity + 0x1c);      // e.g., speed multiplier
        float innerRadius = *(float*)((uintptr_t)entity + 0x38);      // +0x38
        float outerRadius = *(float*)((uintptr_t)entity + 0x3c);      // +0x3c
        float orientFactor = *(float*)((uintptr_t)entity + 0x70);     // +0x70
        float orientX    = *(float*)((uintptr_t)entity + 0x74);       // +0x74
        float orientY    = *(float*)((uintptr_t)entity + 0x78);       // +0x78
        float orientZ    = *(float*)((uintptr_t)entity + 0x7c);       // +0x7c
        float basePosX   = *(float*)((uintptr_t)entity + 0x80);       // +0x80
        float basePosY   = *(float*)((uintptr_t)entity + 0x84);       // +0x84
        float basePosZ   = *(float*)((uintptr_t)entity + 0x88);       // +0x88
        float paramW     = *(float*)((uintptr_t)entity + 0x8c);       // +0x8c (unused in calculation)
        void* audioData  = *(void**)((uintptr_t)entity + 0x454);      // +0x454 -> pointer to audio data
        float dataScale  = *(float*)((uintptr_t)audioData + 0xa4);    // +0xa4 of that struct (volume/scale)

        // Intermediate calculations using global constants
        float speedByFactor = entitySpeed * g_audioSpeedFactor;       // fVar12 from decomp
        float diffRadius = (innerRadius - outerRadius) * speedByFactor; // fVar9
        float sumRadius  = (innerRadius + outerRadius) * speedByFactor; // fVar12 (overwritten)
        float scaleByGlobal = dataScale * g_audioGlobalFactor;        // fVar10

        // Compute new position
        s_activeAudioPosX[count] = scaleByGlobal * orientFactor + basePosX;
        s_activeAudioPosY[count] = scaleByGlobal * orientX + basePosY;
        s_activeAudioPosZ[count] = scaleByGlobal * orientY + basePosZ;
        // The original code immediately overwrites the Z slot with the magnitude, not the Z component
        // This stores the Euclidean magnitude of the velocity/distance vector
        float magnitude = sqrtf(scaleByGlobal * scaleByGlobal + diffRadius * diffRadius + sumRadius * sumRadius);
        s_activeAudioPosZ[count] = magnitude; // kept in the Z parameter slot

        // Set bit 2 (0x4) of flags at +0x460 to mark as active
        *(uint16_t*)((uintptr_t)entity + 0x460) |= 4;

        // Increment global count
        s_activeAudioCount++;
    }
};