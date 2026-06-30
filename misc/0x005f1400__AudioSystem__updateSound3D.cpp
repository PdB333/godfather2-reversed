// FUNC_NAME: AudioSystem::updateSound3D
// Function at 0x005f1400 - updates a 3D sound instance with parameters, handles flags and attenuation

bool AudioSystem::updateSound3D(SoundInstance* pInstance, Sound3DParams* pParams, int extraParam)
{
    bool bError = false;
    
    if (pInstance == nullptr || pParams == nullptr)
        return 0;
    
    unsigned short soundId = *(unsigned short*)((char*)pInstance + 8);  // +0x08: sound handle
    unsigned short flags = *(unsigned short*)((char*)pInstance + 0x10); // +0x10: instance flags (bit2=stop, bit5=update pending)
    
    // If stop flag is set, clear it and return early
    if ((flags & 2) != 0)
    {
        *(unsigned short*)((char*)pInstance + 0x10) = flags & 0xFFFD;
        return 1;
    }
    
    int volume = *(int*)((char*)pInstance + 0x14);  // +0x14: volume or distance (scaled later)
    
    // If pParams has a pitch modification flag, scale the volume
    if ((*(unsigned char*)((char*)pParams + 0x12) & 2) != 0) // +0x12: byte flags
    {
        float fVolume = (float)volume;
        if (volume < 0)
            fVolume += 0x1000000;  // Add large value to round properly? (from DAT_00e44578)
        volume = (int)(fVolume * (float)pParams[1]); // pParams[1] is a float (pitch/scale)
    }
    
    // If delay counter is active, decrement it and skip update triggers
    if (*(char*)((char*)pInstance + 0x1D) != '\0') // +0x1D: delay counter
    {
        *(char*)((char*)pInstance + 0x1D) -= 1;
        goto PostUpdate;
    }
    
    // Check if an update is pending (bit5 of flags)
    if ((flags & 0x20) != 0)
    {
        int* pRelated = *(int**)((char*)pInstance + 0x20); // +0x20: pointer to related object
        if (pRelated == nullptr || *(int*)((char*)pRelated + 0x90) < 0) // +0x90: priority or state
        {
            bError = true;
        }
        else
        {
            short p1 = *(short*)((char*)pParams + 8);  // +0x08: spatial parameter 1 (e.g., pitch)
            float fP1 = (float)(int)p1;
            if (p1 < 0) fP1 += 0x1000000;
            
            float fVolume = (float)volume;
            if (volume < 0) fVolume += 0x1000000;
            
            // Call audio engine to start/update sound with many parameters
            char result = FUN_005eb6d0(
                g_pAudioSystem,            // DAT_01223510 (global audio manager)
                soundId,
                *(int*)((char*)pInstance + 0x0C), // +0x0C: unknown parameter
                *(int*)((char*)pRelated + 0x90),  // priority/state
                fVolume * g_fAttenuation,  // scaled volume (DAT_00e2af48)
                *(float*)((char*)pParams + 12),   // +0x0C: distance or spatial parameter
                fP1 * g_fPitchScale,       // scaled pitch (DAT_00e2af44)
                (float)(int)*(short*)((char*)pParams + 16) * g_fPitchScale, // +0x10: another pitch
                pRelated,
                *(int*)pParams,            // +0x00: some ID
                extraParam                 // passed-in extra parameter
            );
            if (result == '\0') 
            {
                bError = true;
            }
        }
        
        // Clear the update pending flag
        *(unsigned short*)((char*)pInstance + 0x10) &= 0xFEDF;
        
        // If no extra object, set delay counter to 4 to avoid immediate re-update
        if (*(int*)((char*)pInstance + 0x18) == 0) // +0x18: extra object pointer?
        {
            *(char*)((char*)pInstance + 0x1D) = 4;
        }
    }
    
    // Call function to set sound parameters (volume, pitch, distance)
    FUN_005dbc10(
        soundId,
        volume,
        (int)*(short*)((char*)pParams + 8),   // +0x08: pitch value
        (double)(float)*(float*)((char*)pParams + 12) // +0x0C: distance/volume as double
    );
    
PostUpdate:
    // Update engine properties via vtable if flags indicate
    if ((*(unsigned char*)((char*)pParams + 0x12) & 1) != 0) // +0x12: byte flag bit0
    {
        if ((*(unsigned char*)((char*)pInstance + 0x10) & 1) != 0) // instance flag bit0
        {
            *(short*)((char*)pParams + 16) = 0;  // +0x10: reset spatial parameter
        }
        (**(code**)(*(int*)g_pAudioSystem + 0x28))(soundId, pParams + 2); // vtable func: set pan?
    }
    
    if ((*(unsigned char*)((char*)pParams + 0x12) & 2) != 0) // +0x12 bit1
    {
        (**(code**)(*(int*)g_pAudioSystem + 0x2C))(soundId, volume); // vtable func: set volume
    }
    
    if ((*(unsigned char*)((char*)pParams + 0x13) & 1) != 0) // +0x13 bit0
    {
        (**(code**)(*(int*)g_pAudioSystem + 0x30))(soundId, *(int*)pParams); // vtable func: set some int
    }
    
    if (bError)
        return 0;
    
    return 1;
}