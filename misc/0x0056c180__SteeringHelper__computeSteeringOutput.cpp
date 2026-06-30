// FUNC_NAME: SteeringHelper::computeSteeringOutput
// Address: 0x0056c180
// This function computes steering outputs based on a steering input structure.
// It appears to handle both forward and reverse steering modes with angle clamping.
// Input structure offsets: +0x00, +0x04, +0x08, +0x14, +0x20, +0x24, +0x28.

void SteeringHelper::computeSteeringOutput(float* steeringInput, float* outAngle1, float* outIntermediate, float* outAngle2)
{
    float fVar1;
    float fVar2;
    double dVar3;
    float intermediate;
    float fVar4;

    // Constants likely defined elsewhere (possibly in a global config)
    // DAT_00e2a850 = 1.0f (positive direction), DAT_00e446a0 = -1.0f (negative)
    // DAT_00e44564 = 2.0f * PI (angle normalization)
    // DAT_00e2eff4 = some min threshold, DAT_00e2b1a4 = some max threshold
    // DAT_00e2b05c = small epsilon

    if (steeringInput[10] == 0.0f) {
        // Forward steering mode
        fVar2 = steeringInput[8];   // +0x20
        fVar1 = steeringInput[9];   // +0x24
        if (fVar2 == 0.0f) {
            if (fVar1 <= 0.0f) {
                intermediate = DAT_00e2a850;
            } else {
                intermediate = DAT_00e446a0;
            }
            if (steeringInput[0] == 0.0f) {
                fVar2 = 0.0f;
                fVar1 = DAT_00e2a850;
                if (0.0f < steeringInput[2]) {
                    fVar1 = DAT_00e446a0;
                }
            } else {
                dVar3 = (double)steeringInput[0];
                FUN_00b9a9fa();          // likely normalize or wrap angle
                fVar1 = DAT_00e44564 - (float)dVar3;
                fVar2 = 0.0f;
            }
        } else {
            fVar4 = DAT_00e2eff4;
            if ((DAT_00e2eff4 < fVar1) && (fVar4 = DAT_00e2b1a4, fVar1 < DAT_00e2b1a4)) {
                fVar4 = fVar1;
            }
            dVar3 = (double)fVar4;
            FUN_00b9c766();              // likely clamp to range
            intermediate = DAT_00e44564 - (float)dVar3;
            dVar3 = (double)intermediate;
            FUN_00b99e20();              // likely sign check
            fVar1 = DAT_00e446a0;
            if (0.0f < (float)dVar3 * fVar2) {
                fVar1 = DAT_00e2a850;
            }
            if (steeringInput[5] == 0.0f) {
                fVar2 = DAT_00e446a0;
                if (0.0f < steeringInput[1] * (float)dVar3) {
                    fVar2 = DAT_00e2a850;
                }
            } else {
                dVar3 = (double)steeringInput[1];
                FUN_00b9a9fa();
                fVar2 = (float)dVar3;
            }
        }
    } else {
        // Reverse steering mode
        dVar3 = (double)steeringInput[8];
        FUN_00b9a9fa();
        fVar1 = (float)dVar3;
        fVar2 = steeringInput[9];
        fVar4 = DAT_00e2eff4;
        if ((fVar2 <= DAT_00e2eff4) || (fVar4 = DAT_00e2b1a4, DAT_00e2b1a4 <= fVar2)) {
            fVar2 = fVar4;
        }
        dVar3 = (double)fVar2;
        FUN_00b9c766();
        intermediate = DAT_00e44564 - (float)dVar3;
        if (steeringInput[5] == 0.0f) {
            fVar4 = steeringInput[1];
            if (fVar4 == 0.0f) {
                fVar2 = 0.0f;
            } else {
                dVar3 = (double)intermediate;
                FUN_00b99e20();
                fVar2 = DAT_00e446a0;
                if (DAT_00e2b05c < (float)dVar3 * fVar4) {
                    fVar2 = DAT_00e2a850;
                }
            }
        } else {
            dVar3 = (double)steeringInput[1];
            FUN_00b9a9fa();
            fVar2 = (float)dVar3;
        }
    }

    // Write outputs if pointers are non-null
    if (outAngle1 != nullptr) {
        *outAngle1 = fVar1;
    }
    if (outAngle2 != nullptr) {
        *outAngle2 = fVar2;
    }
    if (outIntermediate != nullptr) {
        *outIntermediate = intermediate;
    }
}