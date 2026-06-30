// FUNC_NAME: SoundManager::isSoundAudible
undefined1 SoundManager::isSoundAudible(float *soundPosition, char useNoiseFactor, char useMinRange)
{
    float dx, dz, distSq;
    int numListeners;
    int i;
    int listenerPtr;
    int emitterHandle;
    bool isValid;
    float4 emitterPos; // local_28, local_24, local_20
    float4 listenerInfo; // local_1c (orientation etc.)
    float directionX, directionY;
    float rangeMultiplier;
    float10 temp;
    float angleFactor, dotProduct;
    double magnitudeSq;
    float ratio;

    // Global pointers (inferred from DAT_01223394, DAT_012233a0)
    void* globalState = (void*)DAT_01223394; // +0x10, +0x54, +0x58, +0x5c, +0x70
    uint* listenerArray = (uint*)DAT_012233a0; // array of pointers

    // Quick early checks
    if (*(char*)(globalState + 0x10) != 0 && *(char*)(globalState + 0x54) != 0) {
        float maxRange = *(float*)(globalState + 0x5c);
        float currentRange = *(float*)(globalState + 0x70);
        int useFullRange = *(int*)(globalState + 0x58);
        if (maxRange <= currentRange) {
            if (useFullRange == 0) return 1;
        } else {
            float ratio = currentRange / maxRange;
            if (useFullRange != 0) ratio = 1.0f - ratio;
            if (ratio >= 1.0f) return 1;
        }
    }

    // No listeners? Return not audible
    if (DAT_0122339c == 0 || DAT_012233a0 == 0) return 0;

    numListeners = FUN_0043ff40(); // Get count of active listeners
    if (numListeners == 0) return 0;

    for (i = 0; i < numListeners; i++) {
        listenerPtr = *(int*)(*(int*)(listenerArray + 4) + i * 4);
        if (listenerPtr == 0 || listenerPtr == 0x1f30) continue;

        emitterHandle = *(uint*)(listenerPtr + 0x564); // Sound emitter handle
        isValid = FUN_00424f20(emitterHandle);
        if (!isValid) continue;

        // Get emitter position
        FUN_00424fb0(&emitterPos, emitterHandle);
        dx = soundPosition[0] - emitterPos.x;
        dy = soundPosition[1] - emitterPos.y; // Note: y is vertical in Godfather?
        dz = soundPosition[2] - emitterPos.z;
        distSq = dx*dx + dz*dz;

        // If horizontal distance is smaller than vertical distance and within threshold, skip
        if (distSq < dy*dy && distSq < DAT_00d5e288) {
            return 0; // Not audible
        }

        // Get listener orientation info
        FUN_00425060(&listenerInfo, emitterHandle);
        directionX = listenerInfo.z; // Actually local_18 was from the struct
        directionY = DAT_00d5ee64; // Default forward range
        rangeMultiplier = DAT_00d5ee64; // base range

        if (useMinRange == 0) rangeMultiplier = 0.0f;

        if (useNoiseFactor != 0) {
            temp = (float10)FUN_004251e0(emitterHandle); // some noise angle/volume
            angleFactor = (float)((uint)(float)temp & DAT_00e44680);
            if (_DAT_00d5ca1c < angleFactor) {
                if (DAT_00e446f4 < angleFactor) angleFactor = DAT_00e446f4;
                rangeMultiplier = angleFactor * _DAT_00d5ee60 + rangeMultiplier;
                if ((float)temp >= 0.0f) {
                    directionX = _DAT_00d5c458 * rangeMultiplier + directionX;
                } else {
                    directionX = DAT_00e44718 * rangeMultiplier + directionX;
                }
            }
        }

        // Update global listener direction if changed
        if (directionX != _DAT_0112a6cc) {
            double oldDir = (double)directionX;
            _DAT_0112a6cc = directionX;
            FUN_00b99fcb();
            DAT_0112a6c8 = (float)oldDir;
            double newDir = (double)directionX;
            FUN_00b99e20();
            DAT_00e50dd0 = (float)newDir;
        }

        // Dot product of listener facing direction and sound direction (2D)
        dotProduct = DAT_00e50dd0 * dz + DAT_0112a6c8 * dx;

        if (dotProduct > 0.0f) {
            temp = (float10)FUN_00425130(emitterHandle); // get maximum hearing distance
            float totalRange = (float)(temp + (float10)rangeMultiplier);
            if (temp + (float10)rangeMultiplier != (float10)_DAT_00e50dcc) {
                double d = (double)(totalRange * _DAT_00d5c458);
                _DAT_00e50dcc = totalRange;
                FUN_00b99e20();
                DAT_0112a6c4 = (float)d * (float)d; // squared threshold
            }

            magnitudeSq = dx*dx + dz*dz;
            if (DAT_0112a6c4 <= (dotProduct * dotProduct) / magnitudeSq) {
                return 0; // Outside cone
            }
        }

        return 1; // Audible
    }

    return 0;
}