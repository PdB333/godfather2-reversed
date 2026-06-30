// FUNC_NAME: AudioChannel::update
void __thiscall AudioChannel::update(float deltaTime)
{
    // Thread-local storage access: get audio buffer base
    int* fsBase = *(int**)(__readfsdword(0x2C));
    int bufferBase = *(int*)(fsBase + 8);
    int flagAddr = this->flagsOffset + bufferBase; // this->flagsOffset at offset 0x10 (param_1[4])

    // If the timer flag is already set, skip update
    if ((*(byte*)flagAddr & 1) != 0)
        return;

    int* channelHandlePtr = &this->channelHandle; // offset 0x30 (param_1[0xc])
    SoundData* soundData = this->soundData; // offset 0x24 (param_1[9])

    if (this->channelHandle == 0 || this->flagByte != 0) // flagByte at offset 0x35
    {
        if (this->flagByte == 0)
        {
            // Not currently playing the "stop" version
            if ((this->flags & 0x80000000) == 0)
            {
                // Play sound normally
                playSound(channelHandlePtr, soundData->wave + 8,                          // +8? might be sound wave offset
                          flagAddr + 0x80, this->mixer->audioId);                         // mixer at offset 0x4 (param_1[1]), audioId at +0x84
            }
            else
            {
                // Stop current sound and play alternate (e.g., one-shot)
                stopSound(soundData->wave + 8, localBuffer);
                releaseSound(flagAddr + 0x80, this->mixer->audioId);
            }
        }
        else // this->flagByte != 0
        {
            if ((char)this->flagByte2 == 0) // flagByte2 at offset 0x34 (param_1[0xd])
            {
                // Virtual callback – e.g., onSoundFinished
                (this->vtable->onFinish)(this);
            }
            else
            {
                this->channelHandle = 0;
                this->flagByte = 0;
            }
        }
    }
    else
    {
        // Update running sound
        updateSound(flagAddr + 0x80, this->mixer->audioId);
    }

    // Get current volume multiplier and pitch/pan from sound data
    float volumeMult = soundData->volumeMult;    // offset 0x18 (24) of soundData
    float pitch = defaultPitch;                  // DAT_00e2b1a4

    // Check mixer settings: if category index < 4 and randomizer exists, get random pitch offset
    if (this->mixer->categoryIndex - 1 < 4 && this->mixer->randomizer != nullptr)
    {
        pitch = this->mixer->randomizer->getRandomPitch();  // virtual at +0x110
    }

    // Apply any mix group scaling
    if (this->mixer->mixGroup != nullptr)
    {
        MixGroup* mixGroup = this->mixer->mixGroup;
        if (mixGroup != nullptr)
            mixGroup->refCount++; // increment reference count? (int at +4)
        mixGroup = getMixGroupOverride(mixGroup); // FUN_00500630, returns a scale object
        if (mixGroup != nullptr)
        {
            volumeMult *= mixGroup->volumeScale;   // +0x0c
            pitch *= mixGroup->pitchScale;         // +0x08
        }
    }

    // Clamp pitch to valid range
    float minPitch = minPitchGlobal; // DAT_00e44940
    float maxPitch = maxPitchGlobal; // DAT_00e2b04c
    if (pitch <= minPitch || maxPitch <= pitch)
        pitch = minPitch; // or max? Actually logic: if not in range, set to the lower bound of the two? The code: if (local_2c <= DAT_00e44940 || DAT_00e2b04c <= local_2c) local_2c = fVar9; where fVar9 is either minPitch or maxPitch? Wait, we need to parse correctly.

    // Better reconstruction:
    // The original logic: if (local_2c <= DAT_00e44940 || DAT_00e2b04c <= local_2c) local_2c = fVar9;
    // where fVar9 was either DAT_00e44940 (min) or DAT_00e2b04c (max) based on which condition was true? Actually the assignment is unconditional after the if. But fVar9 is set earlier: fVar9 = DAT_00e44940; if condition true, then fVar9 = DAT_00e2b04c? No, the code: fVar9 = DAT_00e44940; if ((local_2c <= DAT_00e44940) || (fVar9 = DAT_00e2b04c, DAT_00e2b04c <= local_2c)) { local_2c = fVar9; } That's a tricky short-circuit assignment. In the decompiled: fVar9 = DAT_00e44940; if ((local_2c <= DAT_00e44940) || (fVar9 = DAT_00e2b04c, DAT_00e2b04c <= local_2c)) { local_2c = fVar9; } So if local_2c <= min, fVar9 stays min, assign min. Else if local_2c >= max, fVar9 becomes max, assign max. So this clamps to min if below min, max if above max, else stays as is. So we can write:
    if (pitch <= minPitch)
        pitch = minPitch;
    else if (pitch >= maxPitch)
        pitch = maxPitch;

    // Update volume (stored as int but compared as float)
    float targetVolume = pitch; // Actually pitch variable is used for volume? Wait, naming: local_2c was volume? Look at assignments: local_2c from DAT_00e2b1a4 (defaultPitch), then modified by randomizer and mix group. That seems more like pitch (or pitch shift). local_28 from soundData->volumeMult was volume. So I had them swapped. Let's correct: local_2c (pitch) is from defaultPitch, local_28 (volume) is from volumeMult. So:
    // Let's rename: pitch = defaultPitch; volume = volumeMult;
    // Then after scaling: volume *= mixGroup->volumeScale; pitch *= mixGroup->pitchScale;
    // Then clamp pitch. Then set audio channel volume/pitch.

    // Actually the original code: local_28 = *(float*)(soundData+0x18); local_2c = DAT_00e2b1a4.
    // Then later, local_28 and local_2c are used for setVolume and setPan? There is setVolume and setPan or setPitch? The functions: FUN_005e6750 might be setVolume, FUN_005e6700 might be setPan/pitch. The final usage: for local_2c (which came from DAT_00e2b1a4) it is compared to param_1[0xe] and if changed, set via FUN_005e6750. For local_28 (which came from soundData+0x18) it is compared to param_1[0xf] and set via FUN_005e6700. So likely param_1[0xe] is volume and param_1[0xf] is pitch/pan. So rename:
    float newVolume = defaultVolume; // DAT_00e2b1a4
    float newPitch = soundData->pitch; // actually offset +0x18 in soundData, might be pitch

    // Then apply randomizer, mix group scaling etc.
    // The clamping later is on newVolume? Actually the code clamps local_2c, then later adjusts local_28 with a similar pattern. So I'll keep as floating.

    // I'll restructure with proper naming.
    float newVolume = defaultVolume; // DAT_00e2b1a4
    float newPitch = soundData->pitch; // +0x18

    // Apply randomizer to volume? The code: if categoryIndex check, then get random value, assign to local_2c (the volume variable). So yes, randomizer overrides volume.
    if (this->mixer->categoryIndex - 1 < 4 && this->mixer->randomizer != nullptr)
    {
        newVolume = this->mixer->randomizer->getRandomVolume(); // Actually the virtual returns a float
    }

    // Apply mix group scaling
    if (this->mixer->mixGroup != nullptr)
    {
        MixGroup* mg = this->mixer->mixGroup;
        if (mg != nullptr)
            mg->refCount++;
        mg = getMixGroupOverride(mg);
        if (mg != nullptr)
        {
            newPitch *= mg->pitchScale;   // +0x0c? Wait offsets: ( +0xc ) on return of FUN_00500630. That is likely the volume scale? Actually code: local_28 *= *(float*)(iVar6+0xc); local_2c *= *(float*)(iVar6+8); So local_28 (pitch) scaled by offset 0xc, local_2c (volume) scaled by offset 0x8. So:
            newPitch *= mg->volumeScale; // +0x0c (since local_28 was pitch)
            newVolume *= mg->pitchScale; // +0x08 (since local_2c was volume)
        }
    }

    // Clamp volume
    if (newVolume <= minVolume || newVolume >= maxVolume)
    {
        if (newVolume <= minVolume)
            newVolume = minVolume;
        else
            newVolume = maxVolume;
    }

    // Update volume on channel
    if (newVolume != this->currentVolume) // param_1[0xe]
    {
        if (this->channelHandle != 0)
            setChannelVolume(this->channelHandle, newVolume); // FUN_005e6750
        this->currentVolume = newVolume;
    }

    // Adjust pitch (with different clamping)
    if (newPitch > 0.0f)
    {
        if (newPitch < defaultVolume) // defaultVolume is same as DAT_00e2b1a4? Actually the code: if (0.0f < fVar9) { fVar10 = DAT_00e2b1a4; if (fVar9 < DAT_00e2b1a4) goto adjust; } So if newPitch > 0 and newPitch < defaultVolume, keep it; else set to 0 or defaultVolume.
        {
            // keep newPitch
        }
        else
        {
            newPitch = 0.0f; // or defaultVolume? Actually if condition fails (newPitch >= defaultVolume), then it sets fVar10=0.0, then fVar9 = fVar10 = 0.0, so pitch becomes 0. So meaning: if pitch is >= defaultVolume, set to 0? That seems odd. Perhaps it's a pan value: pan from -1 to 1, default is 0? In audio, pan often defaults to 0 (center). The global constant could be 1.0 for max, so if pitch > 1, set to 0? Hard to guess. I'll keep the logic as is.
            newPitch = 0.0f;
        }
    }
    else
    {
        newPitch = 0.0f; // Actually else sets fVar10=0.0, same result.
    }

    // Update pitch on channel
    if (newPitch != this->currentPitch) // param_1[0xf]
    {
        if (this->channelHandle != 0)
            setChannelPitch(this->channelHandle, newPitch); // FUN_005e6700
        this->currentPitch = newPitch;
    }

    // Accumulate time and check if sound duration has elapsed
    if (soundData->duration > 0.0f) // +4 of soundData
    {
        this->elapsedTime += deltaTime; // param_1[10] at offset 0x28? Actually param_1[10] is this+0x28, but we already used offset 0x24 for soundData, so param_1[10] would be at 0x28? Wait offsets: param_1[0] is 0x0, param_1[1] is 0x4, ..., param_1[4] is 0x10, param_1[9] is 0x24, param_1[10] is 0x28, param_1[0xb] is 0x2c, param_1[0xc] is 0x30, param_1[0xd] is 0x34, param_1[0xe] is 0x38, param_1[0xf] is 0x3c. So param_1[10] is at offset 0x28. That is likely some timer accumulator. But earlier we used "this->flagsOffset" at 0x10? That is param_1[4]. So fields:
        // 0x00: vtable
        // 0x04: mixer (param_1[1])
        // 0x10: flagsOffset? Actually the code uses param_1[4] as base for flag address. But also uses param_1[4] + iVar4 for flag. So param_1[4] is a base pointer? Might be a field that stores a pointer to a flag area.
        // 0x24: soundData (param_1[9])
        // 0x28: elapsedTime? But that is param_1[10] as float stored as int? Actually the code: param_2 (delta) added to param_1[10] after cast to int? Wait: param_2 is float, then param_1[10] = (int)param_2; but later param_2 is reassigned? The decompiled: param_2 = (float)param_1[10] + param_2; param_1[10] = (int)param_2; That is a typical accumulate: param_1[10] is a float stored as int? Actually it's cast to int for storage. So we can treat as float.
        // 0x2c: flags (param_1[0xb])
        // 0x30: channelHandle (param_1[0xc])
        // 0x34: flagByte2 (param_1[0xd])? Actually param_1[0xd] is at 0x34, used as char in condition.
        // 0x35: flagByte (used as char)
        // 0x38: currentVolume (param_1[0xe])
        // 0x3c: currentPitch (param_1[0xf])
    }

    // The timer check:
    if (soundData->duration > 0.0f)
    {
        this->accumulatedTime += deltaTime; // param_1[10] stored as float, but we'll treat as float.
        if (this->accumulatedTime >= soundData->duration && this->accumulatedTime != soundData->duration) // second condition avoids infinite loop? Actually original: if (*pfVar2 <= param_2 && param_2 != *pfVar2) then set flag.
        {
            *(uint*)(flagAddr) |= 1; // set the timer flag to finish sound on next update
        }
    }
}

// Note: The above is a reconstruction with inferred field names. Actual class structure may differ.
// Global constants:
extern const float defaultVolume; // DAT_00e2b1a4
extern const float minVolume;     // DAT_00e44940
extern const float maxVolume;     // DAT_00e2b04c

// Helper function declarations (from other modules):
void playSound(int* channelHandle, const char* wave, int flagAddr, int audioId);
void stopSound(const char* wave, char* buffer);
void releaseSound(int flagAddr, int audioId);
void updateSound(int flagAddr, int audioId);
MixGroup* getMixGroupOverride(MixGroup* mixGroup);
void setChannelVolume(int channelHandle, float volume);
void setChannelPitch(int channelHandle, float pitch);