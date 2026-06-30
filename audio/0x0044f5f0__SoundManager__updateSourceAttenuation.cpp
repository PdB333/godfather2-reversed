// FUNC_NAME: SoundManager::updateSourceAttenuation
void __thiscall SoundManager::updateSourceAttenuation(float (*sourceTransform)[3], void* sourceObj, uint sourceFlags)
{
    int local_data_ptr;
    uint flags_from_table;
    int data_base;
    float distance;
    float dx, dy, dz;
    __m128 vec128;
    float scaleFactor;
    float volume;

    // Get per-thread data (FS segment offset 0x2c -> some manager)
    local_data_ptr = *(int*)(*(int*)(__readfsdword(0x2c) + 8) + 0x00); // +0x2c => some TLS slot, +8 => pointer to data
    // Actually the original: iVar1 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
    // This is a typical pattern for accessing a global singleton via thread-local storage.

    // offset +0x18 is an index into a per-instance table
    flags_from_table = *(uint*)(local_data_ptr + 0x7c + *(int*)(this + 0x18));
    data_base = local_data_ptr + *(int*)(this + 0x18);

    // Check source flags against the mask
    if ((sourceFlags & flags_from_table) == 0)
        return;

    // Check additional conditions on the source object
    // sourceObj+0x94 is a byte with bit 8 (0x08) related to "active" or "play3D"
    // sourceObj+0x90 is probably a pointer to a transform or something
    bool condition1 = (flags_from_table & 2) != 0 ||
                      ( (*(byte*)(sourceObj + 0x94) & 8) != 0 && *(int*)(sourceObj + 0x90) != 0 );
    bool condition2 = (flags_from_table & 1) != 0 ||
                      ( (*(byte*)(sourceObj + 0x94) & 8) == 0 || *(int*)(sourceObj + 0x90) == 0 );

    if (!condition1 || !condition2)
        return;

    // Copy the source transform (float[3]) into local buffer
    __m128 localVec = *(__m128*)sourceTransform; // 12 bytes, but we use std::array or just access fields
    // We'll handle as array: 
    float vec[3];
    vec[0] = (*sourceTransform)[0];
    vec[1] = (*sourceTransform)[1];
    vec[2] = (*sourceTransform)[2];

    // If this+0x20 == 0x12, compute distance to listener position (stored at data_base+0x30,0x34,0x38)
    if (*(int*)(this + 0x20) == 0x12) // listener type?
    {
        dx = vec[0] - *(float*)(data_base + 0x30);
        dy = vec[1] - *(float*)(data_base + 0x34);
        dz = vec[2] - *(float*)(data_base + 0x38);
        distance = sqrt(dx*dx + dy*dy + dz*dz);
    }
    else
    {
        distance = 0.0f;
    }

    // Call helper to compute initial volume/pan? Name: FUN_0044f2e0 -> maybe computeSourceVolume
    computeSourceVolume(vec, distance, *(uint32*)(sourceTransform + 12)); // sourceTransform+12 is some extra data?

    // Check distance against global threshold (minimum distance for attenuation)
    if (distance <= *(float*)0x00e2e534) // DAT_00e2e534
        return;

    // Clamp a vector from data_base+0x40 (maybe listener orientation or volume curve)
    __m128 orientationVec = *(__m128*)(data_base + 0x40);
    __m128 minVal = *(__m128*)0x00e31640; // _DAT_00e31640
    __m128 maxVal = *(__m128*)0x00e31650; // _DAT_00e31650
    __m128 clamped = _mm_min_ps(_mm_max_ps(orientationVec, minVal), maxVal);

    // Use clamped vector to compute scale factor
    if ( (flags_from_table & 0x1000) == 0 )
    {
        // fStack_18 is part of the SSE result; we need to extract components
        // Original: fVar4 = (fStack_18 + (float)clamped.m128_f32[1] + (float)clamped.m128_f32[0]) * DAT_00e4461c;
        // Actually the original uses _local_20 which was the transformed vector, but it's been overwritten?
        // Let's parse carefully: after the minps/maxps, the result is stored in _local_20 (which is the same as the original vector? No, local_20 is a 8-byte undefined? Actually it's misleading. The code does: 
        // auVar5 = minps(...); _local_20 = maxps(auVar5, _DAT_00e31640); 
        // So _local_20 is now the clamped vector (but only 8 bytes? Actually it's 16 bytes but local_20 is defined as 8 bytes, but the assignment overwrites only 8? This is likely a Ghidra decompilation artifact. In reality, the entire 16-byte SSE register is stored to a float[3] or float[4] local.
        // We'll assume the clamped vector is in a local array of 3 floats.
        float clampedVec[4];
        _mm_store_ps(clampedVec, clamped);
        scaleFactor = (clampedVec[2] + clampedVec[1] + clampedVec[0]) * *(float*)0x00e4461c; // DAT_00e4461c
    }
    else
    {
        scaleFactor = *(float*)(data_base + 0x88); // some stored value
    }

    // If the scaled distance exceeds an additional threshold, and source type is not "2" (maybe not a single shot?)
    if ( (*(float*)0x00e44598 < scaleFactor * distance) && (*(int*)(this + 0x20) != 2) )
    {
        // Set volume/attenuation value and apply
        *(float*)(data_base + 0x84) = scaleFactor * distance;
        applySourceVolume(sourceObj, &clamped, this); // FUN_00450210
    }
}