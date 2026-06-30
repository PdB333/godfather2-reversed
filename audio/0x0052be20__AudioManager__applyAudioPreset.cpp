// FUNC_NAME: AudioManager::applyAudioPreset

void AudioManager::applyAudioPreset(float crossfadeTime, uint areaId, bool isIndoor) {
    int channelIndex;
    uint tmp;
    uint prevAreaId;
    uint currentAreaId;
    float currentTime;
    float storedTime;
    uint newAreaId;
    uint* allocBuffer;

    if (areaId == 0) {
        // Use default area ID based on indoor/outdoor flag
        areaId = gDefaultAreaIDs[isIndoor ? 1 : 0];
    }

    storedTime = isIndoor ? gIndoorTime : gOutdoorTime;
    currentTime = crossfadeTime - storedTime;

    newAreaId = gDefaultAreaIDs[isIndoor ? 1 : 0];
    if (!(0.0f < currentTime) && areaId == newAreaId) {
        // No change needed
        return;
    }

    // Stop any currently playing audio channel
    if (gCurrentAudioChannelID != 0xFFFFFFFF && gCurrentAudioChannelID < 0x1000) {
        channelIndex = gCurrentAudioChannelID * 0x38;
        if (gAudioChannels[channelIndex] != nullptr && (gAudioChannels[channelIndex]->state & 0xFF) < 4) {
            if (gAudioChannels[channelIndex]->data != 0) {
                FUN_00606e60(gAudioChannels[channelIndex]->data, 0x100000); // release/mute
            }
            gAudioChannels[channelIndex]->flags = (gAudioChannels[channelIndex]->flags & 0xfc9c8fff) | 0x100000;
            FUN_006189c0(); // update channel
        }
    }

    // Find and deactivate the matching audio area entry
    for (uint i = 0; i < 20; i++) {
        if (gAudioAreaIDs[i] == newAreaId) {
            if (i < 20) {
                gAudioAreaFlags[i] = gAudioAreaFlags[i] & 0xFFFFFFFC; // clear active bits
            }
            break;
        }
    }

    // Store previous area ID
    prevAreaId = gPreviousAreaID;
    currentAreaId = gCurrentAreaID;
    gPreviousAreaID = 0;
    gCurrentAreaID = newAreaId;

    // Call update functions
    FUN_00609340(0, currentAreaId, prevAreaId);
    FUN_00609810(1); // activate
    FUN_0060db60(0, 0, 0, 1.0f, 1.0f); // set fade values

    // Set mixer parameters for various bands
    if (gMixerMin < 0x16) gMixerMin = 0x16;
    if (0x16 < gMixerMax) gMixerMax = 0x16;
    gMixerValues[0x30] = 1;

    if (gMixerMin < 0x0E) gMixerMin = 0x0E;
    if (0x0E < gMixerMax) gMixerMax = 0x0E;
    gMixerValues[0x10] = 0;

    if (gMixerMin < 7) gMixerMin = 7;
    if (7 < gMixerMax) gMixerMax = 7;
    gMixerValues[0x14] = 0;

    if (gMixerMin < 0x19) gMixerMin = 0x19;
    if (0x19 < gMixerMax) gMixerMax = 0x19;
    gMixerValues[0x3C] = 5;

    if (gMixerMin < 0x18) gMixerMin = 0x18;
    if (0x18 < gMixerMax) gMixerMax = 0x18;
    gMixerValues[0x38] = 0;

    if (gMixerMin < 0x0F) gMixerMin = 0x0F;
    if (0x0F < gMixerMax) gMixerMax = 0x0F;
    gMixerValues[0x14] = 0; // repeated? maybe different offset

    // Apply mixer state
    FUN_00417cf0(1, 2, 1);

    if (gMixerMin < 0x1B) gMixerMin = 0x1B;
    if (0x1A < gMixerMax) gMixerMax = 0x1B;
    gMixerValues[0x44] = 0;

    // Update audio object references
    gAudioObjectA = gAudioObjectB;
    gAudioObjectC = gAudioObjectD;
    gAudioObjectCount = 5;

    // Release old objects if needed
    if (gAudioObjectList == &gAudioObjectDefault) {
        FUN_0060a460(gAudioObjectB);
        FUN_0060a460(gAudioObjectD);
    }

    // Update other audio subsystems
    FUN_00530a60();
    FUN_00530df0();
    FUN_00530ff0();

    // Allocate and fill audio buffer for area transition
    allocBuffer = (uint*)FUN_0060cd00(0x0D, 4, 0, 1, 0);
    if (allocBuffer != nullptr) {
        allocBuffer[0] = gAudioBufferVal1;
        allocBuffer[1] = gAudioBufferVal2;
        allocBuffer[2] = 0;
        allocBuffer[3] = 0;
        allocBuffer[4] = gAudioBufferVal2;
        allocBuffer[5] = gAudioBufferVal2;
        allocBuffer[6] = gAudioBufferVal2;
        allocBuffer[7] = 0;
        allocBuffer[8] = gAudioBufferVal2;
        allocBuffer[9] = gAudioBufferVal1;
        allocBuffer[10] = gAudioBufferVal2;
        allocBuffer[11] = gAudioBufferVal2;
        allocBuffer[12] = gAudioBufferVal1;
        allocBuffer[13] = gAudioBufferVal1;
        allocBuffer[14] = 0;
        allocBuffer[15] = gAudioBufferVal2;
        FUN_0060cde0(); // commit buffer
    }

    FUN_00612e00(); // flush

    // Clear temporary object references
    gAudioObjectC = 0;
    gAudioObjectA = 0;
    gAudioTemp1 = 0;
    gAudioTemp2 = 0;

    // Set master volume or similar
    FUN_00609890(1);

    // Apply the new area audio
    FUN_0052c420(newAreaId, areaId);
}