// FUNC_NAME: CollisionClamper::clampPosition
bool __thiscall CollisionClamper::clampPosition(const float* inPos, float* outPos) {
    bool clamped = false;

    // First collision volume (sphere-like from DAT_01131064)
    if (this->m_pVolumeList != nullptr) {
        void* volume1 = getCollisionVolume(DAT_01131064);
        if (volume1 != nullptr && (*(byte*)(volume1 + 0x2c) & 1) != 0) {
            // Extract sphere parameters from volume1 at offsets +0x18 (x), +0x1c (y), +0x20 (z), +0x24 (radiusSq)
            float dx = inPos[0] - *(float*)(volume1 + 0x18);
            float dy = inPos[1] - *(float*)(volume1 + 0x1c);
            float dz = inPos[2] - *(float*)(volume1 + 0x20);
            float radiusSq = *(float*)(volume1 + 0x24);
            float distSq = dx * dx + dy * dy + dz * dz;

            if (radiusSq <= distSq) { // point outside sphere
                // Clamp to sphere surface
                float radius = sqrtf(radiusSq); // FUN_00715d50
                // Normalize direction vector
                float normVec[3] = {dx, dy, dz};
                vectorNormalize(normVec, normVec); // FUN_0043a210
                *outPos = *(float*)(volume1 + 0x18) + normVec[0] * (radius - distSq); // distance to surface
                outPos[1] = *(float*)(volume1 + 0x1c) + normVec[1] * (radius - distSq);
                outPos[2] = *(float*)(volume1 + 0x20) + normVec[2] * (radius - distSq);
                clamped = true;
            }

            float volumeY = *(float*)(volume1 + 0x1c);
            float yDiff = volumeY - (clamped ? outPos[1] : inPos[1]);
            // Absolute yDiff via bitmask (assume DAT_00e44680 = 0x7FFFFFFF)
            float absYDiff = *((float*)&((int&)yDiff & 0x7FFFFFFF));
            float yThreshold = *(float*)&_DAT_00d577a0; // some threshold from data

            if (yThreshold <= absYDiff) {
                if (!clamped) {
                    *((uint64_t*)outPos) = *((uint64_t*)inPos);
                    outPos[2] = inPos[2];
                }
                float clampedYLow = volumeY - yThreshold;
                float clampedYHigh = volumeY + yThreshold;
                if (clampedYLow > outPos[1]) {
                    outPos[1] = clampedYLow;
                } else if (outPos[1] > clampedYHigh) {
                    outPos[1] = clampedYHigh;
                }
                clamped = true;
            }
        }
    }

    // Second collision volume (from DAT_0113105c) - likely a different constraint
    if (this->m_pVolumeList != nullptr) {
        void* volume2 = getCollisionVolume(DAT_0113105c);
        if (volume2 != nullptr && checkSecondVolumeFlag()) { // FUN_009b30a0
            initSecondVolumeStuff(); // FUN_009b2900
            void* volumeData = getSecondVolumeData(); // FUN_00471610
            float dx = inPos[0] - *(float*)(volumeData + 0x30);
            float dy = inPos[1] - *(float*)(volumeData + 0x34);
            float dz = inPos[2] - *(float*)(volumeData + 0x38);
            float radius = getSecondRadius(); // FUN_009b2540
            float distSq = dx * dx + dy * dy + dz * dz;

            if (distSq < radius * radius) {
                // Inside second sphere: only Y clamping
                if (!clamped) {
                    outPos[1] = inPos[1];
                } else {
                    // already clamped by first volume, just use current outPos[1]
                }
                float yDiff = *(float*)(volumeData + 0x34) - outPos[1]; // 0x34 is Y
                // Continue below with Y clamping
            } else {
                // Outside second sphere: clamp to surface
                float saveRadius = radius;
                float sqrtRadius = sqrtf(radius); // FUN_00715d50
                float normVec[3] = {dx, dy, dz};
                vectorNormalize(normVec, normVec);
                float distanceToSurface = sqrtRadius - distSq; // not logical, but original code does radius - distSq??
                *outPos = *(float*)(volumeData + 0x30) + normVec[0] * distanceToSurface;
                outPos[1] = *(float*)(volumeData + 0x34) + normVec[1] * distanceToSurface;
                outPos[2] = *(float*)(volumeData + 0x38) + normVec[2] * distanceToSurface;
                float yDiff = *(float*)(volumeData + 0x34) - outPos[1];
                // Now clamp Y
                if (fabs(yDiff) > DAT_00e445ac) {
                    if (!clamped) {
                        *((uint64_t*)outPos) = *((uint64_t*)inPos);
                        outPos[2] = inPos[2];
                    }
                    float low = *(float*)(volumeData + 0x34) - DAT_00e445ac;
                    float high = *(float*)(volumeData + 0x34) + DAT_00e445ac;
                    if (outPos[1] < low) outPos[1] = low;
                    else if (outPos[1] > high) outPos[1] = high;
                    return true;
                }
            }
        }
    }

    if (!clamped) {
        *((uint64_t*)outPos) = *((uint64_t*)inPos);
        outPos[2] = inPos[2];
    }
    return clamped;
}