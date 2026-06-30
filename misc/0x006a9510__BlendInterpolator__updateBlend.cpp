// FUNC_NAME: BlendInterpolator::updateBlend
bool __fastcall BlendInterpolator::updateBlend(BlendInterpolator* this) {
    // Copy current output to intermediate storage (offsets 0xC4-0xD8)
    // These might be previous frame's values or secondary blend targets.
    *(double*)(this + 0xC4) = *(double*)(this + 0xDC);
    *(double*)(this + 0xD0) = *(double*)(this + 0xDC);
    *(float*)(this + 0xCC)  = *(float*)(this + 0xE4);
    *(float*)(this + 0xD8)  = *(float*)(this + 0xE4);

    // Reset start X to a global constant (maybe noise baseline)
    float globalStartX = DAT_01205214;
    this->startX = globalStartX;
    this->blendX = globalStartX;  // +0xD0

    // Check if we should advance the interpolation
    // +0xE8 is a flag probably "isActive" or "shouldContinue"
    // +0xBC is current time, compared to a global threshold (maybe duration)
    if (this->isActive != 0 || this->currentTime < DAT_00e44598) {
        if (this->flagE9 == 0) {
            // Generate random index for a noise table
            uint randomIndex = DAT_010c2678 & DAT_012054b4;
            DAT_012054b4++;

            // Interpolate target X from start X to end X with noise
            // +0xA4 = startX (but overwritten earlier? Actually +0xA4 is separate)
            // +0xA8 = endX
            this->targetX = 
                (this->endX - this->startX) * 
                *(float*)(&DAT_010c2680[randomIndex]) + 
                this->blendX + this->startX;
        } else {
            // If flagE9 is set, just add currentTime + globalStartX to targetX
            this->targetX = this->currentTime + globalStartX;
            this->flagE9 = 0;
        }
    } else {
        // If not active and time >= threshold, reset CC to 0 and set targetX
        *(float*)(this + 0xCC) = 0.0f;
        this->targetX = this->currentTime + globalStartX;
    }

    // Interpolate Y component (offsets 0xAC, 0xB0)
    uint idxY = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4++;
    this->targetY = 
        (this->endY - this->startY) * 
        *(float*)(&DAT_010c2680[idxY]) + 
        this->startY;

    // Interpolate Z component (offsets 0xB4, 0xB8)
    uint idxZ = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4++;
    this->targetZ = 
        (this->endZ - this->startZ) * 
        *(float*)(&DAT_010c2680[idxZ]) + 
        this->startZ;

    // Generate two random booleans via FUN_006a91d0
    bool randA = FUN_006a91d0();
    bool randB = FUN_006a91d0();
    bool combined = randA || randB;
    this->isActive = combined ? 1 : 0;

    if (this->isActive) {
        // Acquire some lock? (DAT_012069c4)
        FUN_00408680(&DAT_012069c4);
        this->flagE9 = 0;
        // Continue the blend sequence (calls back to this or next frame)
        FUN_006a9870();
        return true;
    }
    return false;
}