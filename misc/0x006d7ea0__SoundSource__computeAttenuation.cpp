// FUNC_NAME: SoundSource::computeAttenuation
// Address: 0x006d7ea0
// Computes an attenuation factor based on distance between listener and emitter,
// and interpolates between min/max values stored in the object.

void __thiscall SoundSource::computeAttenuation(SoundSource *this, float *outFactor) {
    float listenerX, listenerZ;        // Listener position (x,z)
    float emitterX, emitterZ;          // Emitter position (x,z)
    float dist;                        // Horizontal distance
    float t;                           // Normalized distance factor
    float lowVal, highVal;             // Interpolation range
    uint8 buffer[24];                  // Temporary buffer for position queries

    // Check if the emitter slot is valid and not a special disabled slot (0x48 = 72)
    if (*(int32 *)((char *)this + 0x260) != 0 && 
        *(int32 *)((char *)this + 0x260) != 0x48) {

        // Retrieve listener position (likely camera or player)
        Vector3 *listenerPos = FUN_00424fb0(buffer, 0);
        listenerX = (float)listenerPos->x;   // Actually reads first 8 bytes as double? But cast to float truncates.
        listenerZ = listenerPos->z;          // Reads next float after the 8-byte block.

        // Determine emitter index from slot + field 0x260
        int emitterIndex;
        if (*(int32 *)((char *)this + 0x260) == 0) {
            emitterIndex = 0;
        } else {
            emitterIndex = *(int32 *)((char *)this + 0x260) - 0x48;
        }

        // Retrieve emitter position (fills a 3-element float buffer: x, y, z)
        // The function writes to buffer starting at &emitterPos, but buffer size is larger.
        float emitterPos[2]; // Actually should be 3 floats, but decompiler split
        float unusedY;       // Corresponds to local_20 (third float from function)
        if (FUN_006c8620(emitterPos, emitterIndex, 4) != false) {
            float listenerXFloat = (float)listenerX; // Re-cast for clarity
            emitterX = emitterPos[0];
            emitterZ = unusedY; // This is the third float written by the function

            // Compute horizontal distance (ignoring Y axis)
            float dx = emitterX - listenerXFloat;
            float dz = emitterZ - listenerZ;
            dist = SQRT(dx * dx + dz * dz);

            // Read distance thresholds from object
            float minDist = *(float *)((char *)this + 0x130);
            if (minDist <= dist) {
                // Normalize distance to [0,1] between minDist and maxRange
                float maxRange = DAT_00e511c0; // Global max range constant
                t = (dist - minDist) / (maxRange - minDist);
            } else {
                t = dist / minDist;
            }

            // Clamp t to [0, clampMax]
            float clampMax = _DAT_00d5780c; // Global clamp maximum (maybe 1.0?)
            if (t <= 0.0f) {
                t = 0.0f;
            } else if (clampMax <= t) {
                t = clampMax;
            } // else t unchanged

            // Choose interpolation range based on whether distance exceeds minDist
            if (minDist <= dist) {
                // Use values at +0x128 and +0x124 as low and high
                lowVal = *(float *)((char *)this + 0x128);
                highVal = *(float *)((char *)this + 0x124);
            } else {
                // Use values at +0x12C (300) and +0x128 as low and high
                lowVal = *(float *)((char *)this + 300);
                highVal = *(float *)((char *)this + 0x128);
            }

            // Linear interpolation
            *outFactor = (highVal - lowVal) * t + lowVal;
        }
    }
}