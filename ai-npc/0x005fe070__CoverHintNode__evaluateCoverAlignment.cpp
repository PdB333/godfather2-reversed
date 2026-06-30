// FUNC_NAME: CoverHintNode::evaluateCoverAlignment
int CoverHintNode::evaluateCoverAlignment(int param_1, int* handleA, int* handleB)
{
    float fVar1;
    char cVar2;
    int state;
    float* posA;
    float* posB;
    float10 fVar6;
    float fVar7;
    float dirToSelf[3];
    float idkPos[3];
    float dirBetween[3];
    float local_30;

    state = *(int*)(param_1 + 0xbc); // +0xbc: cover state (0=none, 1=left, 2=right)
    if (state == 0) {
        state = _rand();
        return (int)((float)state * DAT_00e44590 * _DAT_00e44670); // random fallback
    }
    if ((0 < state) && (state < 3)) {
        if (state == 2) {
            cVar2 = getPosition(&idkPos); // FUN_005fe020 – get some position (possibly from stack)
            if (cVar2 == '\0') {
                state = returnDefaultScore(); // FUN_005fe000
                return state;
            }
        } else {
            // state == 1: use own position
            idkPos[0] = *(float*)(param_1 + 0x30); // +0x30: x
            idkPos[1] = *(float*)(param_1 + 0x34); // +0x34: y
            idkPos[2] = *(float*)(param_1 + 0x38); // +0x38: z
        }
        // Get pointer to handleA's position
        if (*handleA == 0) {
            posA = (float*)0x0;
        } else {
            posA = (float*)handleA[2]; // handleA[0]=valid flag, [2]=ptr to float3
        }
        // Compute vector from handleA's position to own position (or idkPos)
        dirToSelf[0] = idkPos[0] - *posA;
        dirToSelf[1] = idkPos[1] - posA[1];
        dirToSelf[2] = idkPos[2] - posA[2];

        // Get pointer to handleB's position
        if (*handleB == 0) {
            posB = (float*)0x0;
        } else {
            posB = (float*)handleB[2];
        }
        // Compute vector from handleA's position to handleB's position
        dirBetween[0] = *posB - *posA;
        dirBetween[1] = posB[1] - posA[1];
        dirBetween[2] = posB[2] - posA[2];

        // Normalize both vectors
        normalizeVector(&dirToSelf, &dirToSelf); // FUN_0044d680
        normalizeVector(&dirBetween, &dirBetween);

        // Dot product (alignment)
        fVar7 = dirToSelf[0] * dirBetween[0] + dirToSelf[1] * dirBetween[1] + dirToSelf[2] * dirBetween[2];

        // Bit 2 of flags at +0xb4 indicates inverting the alignment
        if ((*(uint*)(param_1 + 0xb4) >> 2 & 1) != 0) {
            fVar7 = DAT_00e44564 - fVar7; // Flip: e.g., 1.0 - dot
        }

        fVar1 = *(float*)(param_1 + 0xb8); // +0xb8: threshold for randomness
        if ((DAT_00e2b05c < fVar1) && (fVar6 = (float10)randomFloat(), fVar6 < (float10)fVar1)) {
            if (fVar1 < DAT_00e2cd54) {
                fVar6 = (float10)randomFloat();
            } else {
                fVar6 = (float10)randomFloat();
                fVar6 = (float10)DAT_00e2cd54 - fVar6;
            }
            fVar7 = (float)(fVar6 * (float10)fVar7);
        }
        return (int)(fVar7 * DAT_00e44858 + DAT_00e44858);
    }
    return 0;
}