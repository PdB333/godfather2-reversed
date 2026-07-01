// FUNC_NAME: TargetingHelper::computeAimTarget
void __thiscall TargetingHelper::computeAimTarget(void *this, float *outTargetPos, float *outTargetDir)
{
    // Incomplete reconstruction - offsets guessed from usage
    float chosenFactor; // fVar12
    float bestDist; // local_90
    int i;
    // struct at +0x58: pointer to character/AI state
    int characterPtr = *(int *)((int)this + 0x58); // this->characterState

    // Check if character is in specific state (maybe cover or combat)
    bool isInSpecialState = false;
    if (!(*(int *)(characterPtr + 0x74c) == 0 ||
          *(int *)(characterPtr + 0x74c) == 0x48 ||
          ((*(uint *)(characterPtr + 0x8e0) >> 10 & 1) == 0)))
    {
        isInSpecialState = true;
    }

    // Determine aiming state from animation
    bool isAiming = false;   // bVar7
    bool isFiring = false;   // bVar6 (or moving?)
    if ((*(byte *)((int)this + 0x90) & 1) != 0) // some action flag
    {
        int animPtr = *(int *)((int)this + 0x188); // pointer to animation state
        int animIndex;
        if (animPtr == 0)
            animIndex = 0;
        else
            animIndex = animPtr + -0x48;

        char animState = *(char *)(animIndex + 0x1b8c); // animation type
        if (animState == 1)
            isAiming = true;
        else if (animState == 2 || animState == 3)
            isFiring = true;
    }

    // Select factor from character state offsets (0x1fd0, 0x1fd4, 0x1fd8) - likely lerp factors
    if (isInSpecialState && isAiming)
        chosenFactor = *(float *)(characterPtr + 0x1fd8);
    else if (!isInSpecialState && !isAiming)
        chosenFactor = *(float *)(characterPtr + 0x1fd0);
    else
        chosenFactor = *(float *)(characterPtr + 0x1fd4);

    // If firing, try to use precomputed target (cover points or nearby enemies)
    if (isFiring)
    {
        bestDist = DAT_00d5f6f0; // large initial distance
        unsigned long long localStructs[4][3]; // each 0x1c bytes? Actually 4 entries, each 0x1c bytes
        // Fill array with up to 4 target candidates
        for (i = 0; i < 4; i++)
            FUN_007ba7e0(&localStructs[i], i); // target query helper

        for (i = 0; i < 4; i++)
        {
            float candDist = *(float *)((int)&localStructs[i] + 0x18); // offset 24? candidate distance
            if (candDist < bestDist && FUN_007ba710(&localStructs[i]) != 0) // valid test
            {
                // Copy position (first 12 bytes) and direction (next 12 bytes)
                float candX = *(float *)(&localStructs[i]);
                float candY = *(float *)((int)&localStructs[i] + 4);
                float candZ = *(float *)((int)&localStructs[i] + 8);
                float dirX = *(float *)((int)&localStructs[i] + 12);
                float dirY = *(float *)((int)&localStructs[i] + 16);
                float dirZ = *(float *)((int)&localStructs[i] + 20);

                outTargetPos[0] = candX;
                outTargetPos[1] = candY;
                outTargetPos[2] = candZ;
                outTargetDir[0] = dirX;
                outTargetDir[1] = dirY;
                outTargetDir[2] = dirZ;

                bestDist = candDist;
                isInSpecialState = true; // reuse flag as "found"
            }
        }
        if (isInSpecialState)
            return; // exit with found target
    }

    // Fallback: compute target from two positions (likely camera and player)
    int cameraPtr = FUN_00471610(); // get camera object
    unsigned long long camPosLow = *(unsigned long long *)(cameraPtr + 0x30);
    float camPosZ = *(float *)(cameraPtr + 0x38);

    int playerPtr = FUN_00471610(); // get player (or character) object
    float playerPosX_low = (float)(*(unsigned long long *)(playerPtr + 0x30));
    float playerPosX_high = (float)(*(unsigned long long *)(playerPtr + 0x30) >> 32);
    float playerPosZ = *(float *)(playerPtr + 0x38);

    // Compute difference vector (player - camera)
    outTargetDir[0] = playerPosX_low - (float)camPosLow;
    outTargetDir[1] = playerPosX_high - (float)(camPosLow >> 32);
    outTargetDir[2] = playerPosZ - camPosZ;

    // Lerp factor from chosenFactor and global constant
    float lerpT = DAT_00e44564 - chosenFactor; // invert factor
    outTargetPos[0] = outTargetDir[0] * lerpT + playerPosX_low;
    outTargetPos[1] = outTargetDir[1] * lerpT + playerPosX_high;
    outTargetPos[2] = outTargetDir[2] * lerpT + playerPosZ;

    return;
}