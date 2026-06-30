// FUNC_NAME: AudioEmitter::GetVolumeForPosition
float AudioEmitter::GetVolumeForPosition(float* position)
{
    float volume = 0.0f;
    
    // Check if we have a valid audio handle (+0x2d4)
    int audioHandle = *(int*)(this + 0x2d4);
    if (audioHandle != 0 && audioHandle != 0x48) // 0x48 may be an invalid handle sentinel
    {
        float dx = position[0];
        float dy = position[1];
        float dz = position[2];
        
        // Get listener position from global object (FUN_00471610)
        void* listener = FUN_00471610(); // returns a struct with position at +0x30,+0x34,+0x38
        dx = *(float*)((int)listener + 0x30) - dx;
        dy = *(float*)((int)listener + 0x34) - dy;
        dz = *(float*)((int)listener + 0x38) - dz;
        
        float distSq = dz*dz + dy*dy + dx*dx; // squared distance to listener
        
        // If within maximum distance (DAT_00d61530)
        if (distSq < DAT_00d61530)
        {
            // Compute pointer to vtable by subtracting 0x48 from audio handle
            int* vtablePtr = (int*)(audioHandle - 0x48);
            
            // Attempt to get an audio object using virtual function (vtable offset 0x10)
            float* outPointer = 0;
            bool success = (**(code**)(*vtablePtr + 0x10))(0x383225a1, &outPointer) != 0;
            if (success && outPointer != 0)
            {
                float dist = sqrtf(distSq) - DAT_00d6144c; // subtract minimum distance offset
                if (dist < 0.0f)
                    dist = 0.0f;
                volume = DAT_00d61528 - dist * _DAT_00d6152c; // linear falloff from max volume
            }
        }
    }
    return volume;
}