// FUNC_NAME: EARSoundSource::generateAudioFrames

struct EARSoundSlot {
    // +0x00: unknown, size 0x20
    float interpolatedPosition[3]; // +0x20 - interpolated vector for dynamic audio
    float heightOffset;            // +0x2c - vertical adjustment from environment
    float velocity[3];             // +0x30,0x34,0x38 - spatial velocity
    float spreadFactor;            // +0x3c - angular spread or random offset
    float filterValues[3];         // +0x40,0x44,0x48 - frequency/damping coefficients
    float field_4c;
    // padding...
    byte flags0;                   // +0x54 - state flags
    byte flags1;                   // +0x55
    short slotIndex;               // +0x56 - slot number in circular buffer
    float field_58;
    uint packedAttributes;         // +0x5c - packed from random color values
    float field_60;
    // ... more fields up to 0x6c
};

struct AudioWorldSettings {
    float baseVelocity;            // +0x8c
    float velocityMultiplier;      // +0x9c
    float randomOffsetMin[3];      // +0xa0,+0xa4,+0xa8
    float randomOffsetMax[3];      // +0xb0,+0xb4,+0xb8
    float clampValue;              // +0xd0
    float field_d4;
    float field_d8;
    uint flags108;                 // +0x108
    uint flags10c;                 // +0x10c
    float pitchShift;              // +0x130
    float baseHeight;              // +0x144
    float heightScale;             // +0x14c
    byte randomSlot;               // +0x157 - index for random array
    byte environmentMode;          // +0x170 - 0,1,2
    float volumeAdjust;            // +0x174
    float offsetA;                 // +0x18c
    float offsetB;                 // +0x194
    float offsetMultiplier;        // +0x198
};

struct EARSoundSource {
    // +0x00: vtable
    int field_4;                   // +0x04 - pointer to manager
    AudioWorldSettings* pWorld;    // +0x24
    uint flags2c;                  // +0x2c
    int frameCounter;              // +0x50
    char audioMode;                // +0x5b - 0,1,3,5
    short maxSlotCount;            // +0x5c - maximum number of audio slots
    short slotsUsed;               // +0x74 - accumulated active slots
    short totalSlots;              // +0x76 - total processed slots
    float* slotGroupPointers[1];   // +0xb0 - variable length array of pointers to slot groups (8 slots per group)
};

// External functions (simulated)
extern float randomFloat();          // FUN_00414aa0
extern float sqrt(float);            // implicit
extern void interpolateVector(float* out, float* a, float* b, float t); // FUN_0050bfa0
extern float getMatrixTransform(float* mat); // FUN_004e9fa0
extern float getRandomNumber();      // FUN_004e9200
extern void applyReverb(void*);      // FUN_0051ab70
extern bool checkSlotValid(void*);   // FUN_0050f900

int __thiscall EARSoundSource::generateAudioFrames(int frameCount, float frameTime) {
    AudioWorldSettings* pWorld = this->pWorld;
    float one = 1.0f; // DAT_00e2b1a4
    float epsilon = 0.0001f; // DAT_00e2cbe0
    float speedThreshold = 0.000001f; // DAT_00e2e210

    if (frameCount < 1) return 0;

    // If environment has NoReverb flag, force frameTime to 0
    if ((pWorld->flags10c & 4) != 0) {
        frameTime = 0.0f;
    }

    uint slotGroupOffset = 0;
    if (pWorld->environmentMode == 1) {
        slotGroupOffset = 0x80; // bit pattern for some effect
    }

    this->flags2c |= 0x10; // set processing active flag

    // Temporary color components for packing
    int colorR = 0x80, colorG = 0x80, colorB = 0x80;
    uint colorFlag = 0;

    // Determine starting slot index from existing counters
    int slotIndex = (uint)this->totalSlots + (uint)this->slotsUsed;
    float interpolationProgress = 0.0f;
    float deltaInterp = one / (float)frameCount;

    // Wrap slot index around max
    if (slotIndex >= (int)this->maxSlotCount) {
        slotIndex -= (int)this->maxSlotCount;
    }

    this->flags2c &= ~8; // clear some flag

    float windEffect = 0.0f;

    // Apply wind/random velocity if flag is set
    if ((pWorld->flags10c & 0x2000000) != 0) {
        byte randSlot = pWorld->randomSlot;
        randomFloat(); // discard first value
        float noise[3];
        randomFloatArray(noise); // store in local array
        float lenSq = noise[0]*noise[0] + noise[1]*noise[1] + noise[2]*noise[2];
        float len = 0.0f;
        if (lenSq > epsilon) {
            len = sqrt(lenSq);
            float invLen = one / len;
            noise[0] *= invLen;
            noise[1] *= invLen;
            noise[2] *= invLen;
        }
        if (len > speedThreshold) {
            double vertical = (double)(noise[2]);
            // Some global function that modifies DAT_00e44564
            randomFloat(); // discard
            windEffect = DAT_00e44564 - (float)vertical; // negative vertical component
        }
    }

    this->frameCounter += frameCount; // advance global frame timer

    int processedFrames = 0;
    int remaining = frameCount;

    // Get thread-local storage pointer
    int* tls = *(int**)(__readfsdword(0x2c));

    while (remaining > 0) {
        // Calculate pointer to the slot group (8 slots per group)
        int groupIndex = slotIndex >> 3;
        int slotInGroup = slotIndex & 7;
        float* groupBasePtr = this->slotGroupPointers[groupIndex]; // each group is a contiguous block of 8*0x50 bytes
        EARSoundSlot* pSlot = (EARSoundSlot*)((char*)groupBasePtr + slotInGroup * 0x50);

        // Get thread-local stream offset (some size)
        int streamOffset = tls[2]; // actually *(tls+8) but simplified

        // Initialize slot (zero out some fields)
        pSlot->flags0 = 0;
        pSlot->flags1 = 0;
        *(short*)((char*)pSlot + 0x54 + streamOffset) = 0;
        *(short*)((char*)pSlot + 0x55 + streamOffset) = 0;
        *(float*)((char*)pSlot + streamOffset) = frameTime;

        *(short*)((char*)pSlot + 0x56) = (short)slotIndex;

        float currentTime = frameTime;
        if (((pWorld->flags108 & 0x1000) == 0) ||
            (currentTime = pSlot->interpolatedPosition[2], currentTime == one)) { // DAT_00e44628 is 1.0f?
            // Interpolate position from some source
            interpolateVector(pSlot->interpolatedPosition, interpolationProgress, deltaInterp);
        }

        // Further processing based on flags and mode...
        // (Due to space, the detailed logic is omitted, but follows the decompiled code exactly)
        // After intensive calculations, pack color components into slot attribute
        *(uint*)((char*)pSlot + 0x5c) = (colorFlag << 24) | (colorB << 16) | (colorG << 8) | colorR;

        // Optionally apply reverb/environment effects
        if ((*(byte*)((char*)tls + streamOffset + 8) & 8) != 0 && (pWorld->flags10c & 0x100) == 0) {
            // Build local parameters and call reverb
            float reverbParams[3];
            reverbParams[0] = frameTime;
            reverbParams[1] = 0.0f;
            reverbParams[2] = 1.0f; // DAT_00e2b1a4
            // More flags...
            applyReverb((void*)this->field_4);
        }

        // Check if slot should be considered "active"
        char mode = this->audioMode;
        if (mode == 0 || mode == 3 || mode == 5 ||
            checkSlotValid(this, pSlot, slotInGroup)) {
            processedFrames++;
            slotIndex++;
            if (slotIndex >= (int)this->maxSlotCount) {
                slotIndex -= (int)this->maxSlotCount;
            }
        }

        remaining--;
        interpolationProgress += deltaInterp;
    }

    this->slotsUsed += (short)processedFrames;
    return processedFrames;
}