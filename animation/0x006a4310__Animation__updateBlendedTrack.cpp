// FUNC_NAME: Animation::updateBlendedTrack
// Function address: 0x006a4310
// Updates an animation blend track with random offset and frame clamping

void __thiscall Animation::updateBlendedTrack(int this, int trackIndex, void* contextPtr, float deltaTime)
{
    uint randIndex;
    int iVar3;
    int frameLimit;
    float blendedValue;
    int roundedValue;
    int trackBase;

    // Each track is 0x30 bytes, starting at this+0x58
    trackBase = trackIndex * 0x30 + *(int *)(this + 0x58);

    // Random table index (global seed and mask)
    randIndex = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;  // increment seed

    // Blend between start (track+0x1c) and end (track+0x20) using random factor from table
    blendedValue = (*(float *)(trackBase + 0x20) - *(float *)(trackBase + 0x1c)) *
                   *(float *)(&DAT_010c2680 + randIndex * 4) + *(float *)(trackBase + 0x1c);

    // If deltaTime is large enough, apply rounding and set audio value
    if (deltaTime <= DAT_00e44598)
        goto LAB_006a4413;

    // contextPtr+8 contains a frame count or limit
    frameLimit = *(int *)((int)contextPtr + 8);
    // Rounded blend value (used for audio parameter)
    roundedValue = (int)(blendedValue * deltaTime + 0.5f);
    FUN_00826410(0, 0, 0, 0, roundedValue);

    iVar3 = *(int *)(trackBase + 0x14); // Some min/max value from track
    if (*(int *)(trackBase + 0x18) < iVar3) {
        if (iVar3 <= frameLimit)
            goto LAB_006a4413;
LAB_006a43e6:
        if (frameLimit <= *(int *)(trackBase + 0x18))
            goto LAB_006a4413;
        if (frameLimit < iVar3)
            goto LAB_006a43ee;
        iVar3 = (iVar3 - frameLimit) + 0x18;
    }
    else {
        if (iVar3 <= frameLimit)
            goto LAB_006a43e6;
LAB_006a43ee:
        iVar3 = iVar3 - frameLimit;
    }

    // Adjust blended value based on clamped difference (0xe10 = 3600, likely frame rate conversion)
    blendedValue = ((float)(iVar3 * 0xe10) + blendedValue * deltaTime) / deltaTime;

LAB_006a4413:
    // Write blended value to global data store keyed by this+0x3c and track offset+0x24, type 5
    FUN_00440590(&DAT_0112a534, this + 0x3c, blendedValue, trackBase + 0x24, 5);
    *(undefined1 *)(trackBase + 0x2c) = 1; // Mark track as updated
    return;
}