// FUNC_NAME: AudioMixer::setChannelMixParameters
// Function address: 0x005f45c0
// Searches for a channel by ID, sets volume and configures auxiliary sends and master send.
// Uses two parallel arrays: channelList at +0x82ac (0x5c stride) and channelData at +0x8210 (0x170 stride).
// Also uses a bus pointer array at +0x81c4 (0x10 stride).

bool __thiscall AudioMixer::setChannelMixParameters(int this, float channelId, float volume)
{
    int index;
    float *channelEntry;
    bool ret;
    int auxSend1Handle;
    int auxSend3Handle;
    int masterSendHandle;
    float scaledVolume;

    ret = false;
    index = 0;
    channelEntry = (float *)(this + 0x82ac); // channel list start

    while ((int)channelEntry[1] < 0 || channelEntry[0] != channelId) {
        index++;
        channelEntry += 0x5c / sizeof(float); // 0x5c = 92 bytes = 23 floats
        if (9 < index) {
            return false;
        }
    }

    if (index >= 0) {
        // Calculate pointer to channel data structure
        int channelDataOffset = index * 0x170 + 0x8210 + this;

        FUN_00ab4db0(&DAT_00e2aea0); // lock mutex

        // Get bus index from channel data at offset 0x9c
        int busIndex = *(int *)(channelDataOffset + 0x9c);
        // Check if corresponding bus pointer in array at this+0x81c4 is non-null
        if (*(int *)(*(int *)(busIndex * 0x10 + 0x81c4 + this)) != 0) {
            // Get handles for auxiliary sends and master send
            auxSend1Handle = FUN_004dafd0("AuxSend1", &channelId);
            int auxSend1Result = FUN_005e9d90(auxSend1Handle, &channelId);
            auxSend3Handle = FUN_004dafd0("AuxSend3", &channelId);
            int auxSend3Result = FUN_005e9d90(auxSend3Handle, &channelId);
            masterSendHandle = FUN_004dafd0("SendToMaster", &channelId);
            int masterSendResult = FUN_005e9d90(masterSendHandle, &channelId);

            if ((DAT_00e2b05c <= *(float *)(channelDataOffset + 0x134)) &&
                (auxSend3Result != 0) && (masterSendResult != 0)) {
                // Set volume at offset 0x90
                *(float *)(channelDataOffset + 0x90) = volume;

                // Scale volume by factor at offset 0x98
                scaledVolume = *(float *)(channelDataOffset + 0x98) * volume;

                FUN_00c9eac0(); // begin volume update

                if (auxSend1Result != 0) {
                    float finalVolume = scaledVolume;
                    if (*(char *)(this + 0x9089) == '\0') { // check mute flag
                        finalVolume = 0.0f;
                    }
                    FUN_00ca4e90(0, finalVolume); // set AuxSend1 volume
                }

                FUN_00ca4e90(0, scaledVolume); // set AuxSend3 volume
                FUN_00ca4e90(0, *(float *)(channelDataOffset + 0x90)); // set master send volume

                FUN_00c9eae0(); // end volume update

                ret = true;
            }
        }
        FUN_00ab4e70(); // unlock mutex
    }
    return ret;
}