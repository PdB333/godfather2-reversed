// FUNC_NAME: PlayerAudio::updateListenerParams
void PlayerAudio::updateListenerParams(void* entity, int controllerId)
{
    int slotIndex = 0;
    int i;

    // Find slot index matching controller ID
    if (g_slotCount > 0)
    {
        int* pSlot = g_slotArray; // each entry is 0x84 bytes, first dword is ID
        for (i = 0; i < g_slotCount; i++)
        {
            if (controllerId == *pSlot)
            {
                slotIndex = i;
                break;
            }
            pSlot = (int*)((char*)pSlot + 0x84); // stride 0x84
        }
    }

    void* pTlsData = *(void**)(__readfsdword(0x2c)); // TLS pointer
    lockMutex(); // FUN_00491090 (possibly thread sync)

    // Check if source data is active for this slot
    char* flagByte = (char*)g_sourceDataFlagArray + slotIndex * 0x210;
    if (*flagByte != 0) // condition simplified: 1 < ((*flagByte != 0)*2 + 1) => true if *flagByte != 0
    {
        // Overwrite controllerId with some other ID from slot data
        controllerId = *(int*)((char*)g_slotData2 + slotIndex * 0x84);

        // Get source data (position/effect parameters)
        uint32_t* pSourceData = (uint32_t*)((char*)g_sourceDataArray + slotIndex * 0x210);
        if (*flagByte == 0)
        {
            pSourceData = (uint32_t*)g_defaultSourceData;
        }

        uint32_t val0 = pSourceData[0];
        uint32_t val1 = pSourceData[1];
        uint32_t val2 = pSourceData[2];
        uint32_t val3 = pSourceData[3];

        // Copy to this object
        *(uint32_t*)(this + 0x2c0) = val0;
        *(uint32_t*)(this + 0x2c4) = val1;
        *(uint32_t*)(this + 0x2c8) = val2;
        *(uint32_t*)(this + 0x2cc) = val3;

        // If this is the local player audio and a related handle exists, set audio source
        if (g_localPlayerAudio == this && *(int*)(this + 0x2bc) != 0)
        {
            AudioSetSourceParams(*(void**)(this + 0x14), *(int*)(this + 0x2bc), (float*)&mSourcePosition);
        }
    }

    // Additional processing
    int paramB = *(int*)((char*)g_slotArray + slotIndex * 0x84); // first dword again
    AudioSystemUpdate(g_someAudioSystem); // FUN_0041f560
    AudioCalculateSomething(this, controllerId, paramB, paramB, g_someGlobalInt); // FUN_004922b0

    // Get current time/frame
    float audioTime = getAudioTime(); // FUN_00414aa0
    if (g_localPlayerAudio == this)
    {
        AudioSetTimeParameter(*(void**)(this + 0x14), *(void**)(this + 0x29c), audioTime); // FUN_0060ad20
    }

    // Compute blend factor from animation or camera data
    int entityIndex = *(int*)(entity + 0x18);
    float blendFactor = (float)*(byte*)(*(int*)(pTlsData + 8) + 0x9b + entityIndex) * g_timeScale; // DAT_00e44640
    // Set two floats (perhaps FOV or distance)
    *(float*)(this + 0x2b4) = g_baseValue - blendFactor; // DAT_00e2b1a4
    *(float*)(this + 0x2b8) = blendFactor;

    if (g_localPlayerAudio == this)
    {
        AudioSetListenerParams(*(void**)(this + 0x14), *(void**)(this + 0x2b0), (float*)(this + 0x2b4)); // FUN_0060ac80
    }
}