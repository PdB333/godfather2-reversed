// FUNC_NAME: AudioManager::updateStreamSlot
void AudioManager::updateStreamSlot(int slotIndex)
{
    char leftStreamId = g_audioState.leftStreamActiveId;  // DAT_012233b4 + 0x564
    char rightStreamId = g_audioState.rightStreamActiveId; // DAT_012233b4 + 0x565

    // Process left audio stream if active (ID != 0x12 = AUDIO_STREAM_INVALID)
    if (leftStreamId != 0x12)
    {
        // Get audio object associated with this stream ID
        IAudioObject* pLeftObj = (IAudioObject*)GetAudioObjectById(leftStreamId);
        // Allocate a free channel handle
        uint32_t channelHandle = GetFreeChannelHandle();
        int newLeftQueueIdx = g_leftStreamQueueHead + 1;
        if (newLeftQueueIdx != 0x10) // ring buffer size 16, cap at index 15
        {
            g_leftStreamQueueHead = newLeftQueueIdx;
            g_leftStreamQueue[newLeftQueueIdx] = channelHandle;
        }
        // Read the left stream parameter from the per-slot table
        uint32_t leftParam = g_slotStreamParamsLeft[slotIndex * 2]; // DAT_01129bd4
        // Call virtual function (offset +8, likely Play/Start) on the audio object
        (pLeftObj->vtable[2])(leftParam);
    }

    // Process right audio stream if active
    if (rightStreamId != 0x12)
    {
        IAudioObject* pRightObj = (IAudioObject*)GetAudioObjectById(rightStreamId);
        uint32_t channelHandle = GetFreeChannelHandle();
        int newRightQueueIdx = g_rightStreamQueueHead + 1;
        if (newRightQueueIdx != 0x10)
        {
            g_rightStreamQueueHead = newRightQueueIdx;
            g_rightStreamQueue[newRightQueueIdx] = channelHandle;
        }
        uint32_t rightParam = g_slotStreamParamsRight[slotIndex * 2]; // DAT_01129bd0
        (pRightObj->vtable[2])(rightParam);
    }
}