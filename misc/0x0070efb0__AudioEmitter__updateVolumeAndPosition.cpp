// FUNC_NAME: AudioEmitter::updateVolumeAndPosition

void __thiscall AudioEmitter::updateVolumeAndPosition(uint param_2, int layerIndex)
{
    float fVar7;
    float fVar6;
    undefined4 uVar1, uVar2, uVar3;
    undefined4 *puVar4;
    float10 fVar5;
    float local_70;
    undefined4 local_80, local_7c, local_78, local_74;
    undefined4 local_6c, local_68, local_64, local_60, local_5c, local_58, local_54;
    undefined1 local_50[48];
    undefined4 local_20, local_1c, local_18, local_14;

    // Initialization if not already done
    if (this->flag_initialized == 0) {
        // Fetch identity matrix from somewhere (possibly global)
        puVar4 = (undefined4 *)getIdentityMatrix();
        // Copy 4x4 matrix to this+0x50 (world transform?)
        uVar1 = puVar4[1];
        uVar2 = puVar4[2];
        uVar3 = puVar4[3];
        this->matrix_0x50[0] = *puVar4;
        this->matrix_0x50[1] = uVar1;
        this->matrix_0x50[2] = uVar2;
        this->matrix_0x50[3] = uVar3;
        uVar1 = puVar4[5];
        uVar2 = puVar4[6];
        uVar3 = puVar4[7];
        this->matrix_0x50[4] = puVar4[4];
        this->matrix_0x50[5] = uVar1;
        this->matrix_0x50[6] = uVar2;
        this->matrix_0x50[7] = uVar3;
        uVar1 = puVar4[9];
        uVar2 = puVar4[10];
        uVar3 = puVar4[0xb];
        this->matrix_0x50[8] = puVar4[8];
        this->matrix_0x50[9] = uVar1;
        this->matrix_0x50[10] = uVar2;
        this->matrix_0x50[11] = uVar3;
        uVar1 = puVar4[0xd];
        uVar2 = puVar4[0xe];
        uVar3 = puVar4[0xf];
        this->matrix_0x50[12] = puVar4[0xc];
        this->matrix_0x50[13] = uVar1;
        this->matrix_0x50[14] = uVar2;
        this->matrix_0x50[15] = uVar3;
        this->flag_initialized = 1; // +0x220
        initOrientation(this->orientationQuat); // +0x404
        resetTimer(); // probably global timer reset
    }

    fVar6 = this->maxVolume; // +0x21c
    fVar7 = 0.0f;
    if (fVar6 != 0.0f) {
        fVar7 = (fVar6 - this->currentVolume) / fVar6; // +0x424
    }

    // Interpolate orientation based on volume ratio
    lerpOrientation(&local_70, this->orientationQuat, fVar7); // +0x404

    if (this->useRandomVolume == 0) { // +0x241
        // Apply random multiplier
        fVar5 = getRandomFloat(); // 0..1
        local_70 = (float)(fVar5 * (float10)local_70);
    } else {
        // Use per-layer volume multiplier
        local_70 = this->layerVolumeMultipliers[layerIndex] * local_70; // +0x2dc + layerIndex*4
    }

    // Apply final volume to audio engine
    setAudioVolume(local_70); // some global function

    // If there's a velocity/direction vector, apply spatial processing
    if ((this->velocityX != 0.0f) || (this->velocityY != 0.0f)) { // +0x214, +0x218
        // Build a matrix from local_54 and other locals
        local_80 = local_60;
        local_7c = local_5c;
        local_78 = local_58;
        local_74 = 0;
        matrixMultiply(local_54, &local_80, local_50);
        local_20 = local_6c;
        local_1c = local_68;
        local_18 = local_64;
        local_14 = _DAT_00d5780c;
        applyDopplerEffect(local_50);
        apply3DAudio(local_50);
    }

    fVar7 = 0.0f;
    fVar6 = this->currentVolume - volumeDecayRate; // DAT_012067e8
    this->currentVolume = fVar6; // +0x424
    if (fVar6 < 0.0f) {
        this->currentVolume = 0; // +0x424
        resetTimer();
        // If there's a trigger volume and a callback object
        if ((this->triggerVolume != 0.0f) && (this->callbackObject != 0)) { // +0x210, +0x3d0
            float angleDiff = this->targetAngle - this->currentAngle; // +0x3e4, +0x404
            if (angleDiff < 0.0f) {
                angleDiff = 2.0f * PI - angleDiff; // DAT_00e44564 assumed 2*PI
            }
            // If angle difference is within threshold and not exactly at threshold
            if ((this->angleThreshold <= angleDiff) && (angleDiff != this->angleThreshold)) { // +0x31c
                triggerCallback(this->callbackObject, param_2, 0); // +0x3d0
            }
        }
    }
    return;
}