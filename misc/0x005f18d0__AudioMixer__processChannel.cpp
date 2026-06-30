// FUNC_NAME: AudioMixer::processChannel
// Address: 0x005f18d0
// Role: Processes a single audio channel's volume and panning, applying envelopes and random variation.

// External globals (from data segment)
extern float DAT_00e2b1a4;       // Master volume scale (e.g., 1.0)
extern float DAT_00e2b04c;       // Some fade multiplier
extern float DAT_00e44680;       // Mask for float manipulation (likely 0x7fffffff)
extern float DAT_00e2b05c;       // Threshold for fade direction
extern float DAT_00e2fc48;       // Step size for fade adjustment
extern void* DAT_01223508;       // Some manager instance (e.g., AudioDataManager)

// Forward declarations of called functions
bool AudioMixer::isSoundLoaded(void* manager, int soundId); // FUN_005dcb60
int AudioMixer::getOutputState();                           // FUN_005f3240
float AudioMixer::getRandomFloat();                         // FUN_00427180 (returns [0,1))
void AudioMixer::setChannelPanVolume(int channelIdx, byte rawVolume, int pan, double volumeScale, double fadeValue);  // FUN_005dbc10 (5-arg version)
void AudioMixer::setChannelPanVolume(int channelIdx, byte rawVolume, int pan, double volumeScale);                    // FUN_005dbc10 (4-arg version)
void AudioMixer::applyEnvelope(int clampedVolume, double fadeValue); // FUN_005f34f0

void AudioMixer::processChannel(SpeakerSlot* slot, MixerContext* context)
{
    float fVar11;
    ushort* pSpeakerCount;
    int* pSoundInfo;
    int streamInfo;
    char indexByte;
    byte volByte;
    int iVar7;
    uint uVar8;
    short sPan;
    float fVar12;
    uint local_58;

    fVar11 = DAT_00e2b1a4;

    if (slot == nullptr || context == nullptr) {
        return;
    }

    pSpeakerCount = (ushort*)(context + 0x30);   // +0x30: pointer to speaker count table
    pSoundInfo = (int*)(context + 0x2c);          // +0x2c: pointer to sound info array
    streamInfo = *(int*)(context + 8);            // +0x08: pointer to stream info structure

    // Validate speaker table and index
    if (pSpeakerCount == (ushort*)0xdeadbeef) {
        return;
    }

    indexByte = *(char*)(slot + 3);   // +0x03: speaker index (0-based)
    if ((ushort)indexByte >= *pSpeakerCount) {
        return;
    }

    // Each speaker slot occupies 0x4A bytes; check pointer validity
    if (pSpeakerCount + (uint)indexByte * 0x4a + 2 == nullptr) {
        return;
    }

    uVar8 = *(uint*)(streamInfo + 8); // +0x08: flags from stream info

    // Check if sound is loaded (maybe a specific sound ID)
    if (pSoundInfo != nullptr && *pSoundInfo != 0) {
        char cVar5 = AudioMixer::isSoundLoaded(DAT_01223508, pSoundInfo[0x17]);
        if (cVar5 != 0) {
            fVar11 = 0.0f; // If loaded, set volume to zero? (or use zero scale)
        }
    }

    fVar11 = *(float*)(context + 0x50) * fVar11; // +0x50: channel volume multiplier

    // Compute pan value: raw volume << 7, scaled by fVar11, then truncated to short
    sPan = (short)(int)((float)(*(int*)(slot + 4) << 7) * fVar11); // +0x04: raw volume (0-255?)

    // Check if pan > 0 or if a specific flag allows negative pan
    if (sPan <= 0 && ((~(uVar8 >> 5) & 1) != 0)) {
        return; // No audible output
    }

    iVar7 = AudioMixer::getOutputState();
    if (iVar7 == 0) {
        // No output state, just set pan/volume without envelope
        AudioMixer::setChannelPanVolume(
            (int)indexByte,
            *(byte*)(slot + 4),   // raw volume
            (int)sPan,
            (double)fVar11
        );
        return;
    }

    // Calculate clamped volume (0-127) from raw volume and a factor from stream info
    uVar8 = (uint)((float)*(byte*)(slot + 4) * *(float*)(streamInfo + 0x20)); // +0x20: some scaling factor
    byte bVar6 = (byte)uVar8;
    if (bVar6 == 0) {
        local_58 = 0;
    } else {
        local_58 = 0x7f; // 127
        if (bVar6 < 0x7f) {
            local_58 = uVar8 & 0xff;
        }
    }

    // Determine fade value
    if ((*(byte*)(context + 0x4a) & 2) == 0) {
        // Not in direct volume mode; compute fade from random and stream info
        fVar12 = DAT_00e2b1a4;
        if (*(float*)(streamInfo + 0x10) > 0.0f) {
            // Randomize fade if not already set
            if (((*(byte*)(streamInfo + 8) & 4) == 0) || (*(float*)(context + 0x7c) == 0.0f)) {
                float random = AudioMixer::getRandomFloat();
                *(float*)(context + 0x7c) = random; // +0x7c: fade timer/phase
            }
            fVar12 = *(float*)(streamInfo + 0x10) * *(float*)(context + 0x7c) * DAT_00e2b04c +
                     (DAT_00e2b1a4 - *(float*)(streamInfo + 0x10));
        }
    } else {
        // Direct volume mode: use a stored value
        fVar12 = *(float*)(context + 0x3c); // +0x3c: direct volume
    }

    // Call the 5-argument version with fade
    AudioMixer::setChannelPanVolume(
        (int)indexByte,
        *(undefined1*)(slot + 4),   // raw volume (treated as byte)
        (int)sPan,
        (double)fVar11,
        (double)fVar12
    );

    // Apply additional envelope if stream info has a second factor
    if (*(float*)(streamInfo + 0x14) > 0.0f) {
        if (((*(byte*)(streamInfo + 8) & 8) == 0) ||
            (fVar11 = *(float*)(context + 0x7c), fVar11 == 0.0f)) {
            // Randomize again
            float random = AudioMixer::getRandomFloat();
            float fVar1 = *(float*)(context + 0x7c);
            fVar11 = 1.0f - random * *(float*)(streamInfo + 0x14);
            // Adjust fade value toward target with step
            if ((float)((uint)(fVar11 - fVar1) & (uint)DAT_00e44680) < DAT_00e2fc48) {
                if (fVar11 - fVar1 <= DAT_00e2b05c) {
                    fVar11 = fVar1 - DAT_00e2fc48;
                } else {
                    fVar11 = fVar1 + DAT_00e2fc48;
                }
            }
            *(float*)(context + 0x7c) = fVar11;
        }
        // Recompute clamped volume with new fade
        uVar8 = (uint)((float)*(int*)(slot + 4) * *(float*)(streamInfo + 0x20) * fVar11);
        bVar6 = (byte)uVar8;
        if (bVar6 == 0) {
            local_58 = 0;
        } else {
            local_58 = 0x7f;
            if (bVar6 < 0x7f) {
                local_58 = uVar8 & 0xff;
            }
        }
    }

    AudioMixer::applyEnvelope(local_58, fVar12);

    *(unsigned short*)(context + 0x4a) = 0; // Clear flags
}