// FUNC_NAME: InterpolationHelper::computeCoefficients
void __thiscall InterpolationHelper::computeCoefficients(float *this) // this is pointer to struct (e.g., InterpolationHelper)
{
    int iVar1;
    int iVar3;
    float fVar4;
    float fVar5;
    float local_c;
    float local_8;

    int iVar2 = (int)this;
    // offset +0x24: pointer to an "animConfig" or "curveData" sub-structure
    int animConfig = *(int *)(iVar2 + 0x24);
    fVar5 = DAT_00e2b1a4; // some constant (likely default slope or time)
    iVar1 = animConfig;
    switch (*(undefined4 *)(animConfig + 0x28)) // offset +0x28: interpolation mode (enum)
    {
    case 1: // Mode 1: Linear interpolation? (fixed speed)
    case 3: // Mode 3: same as 1
        // Compute slope: (endValue - startValue) * speedFactor
        fVar5 = (*(float *)(animConfig + 0x34) - *(float *)(animConfig + 0x38)) * DAT_00e2cd54;
        *(float *)(iVar2 + 0x3c) = fVar5; // +0x3c: slope
        *(float *)(iVar2 + 0x40) = fVar5 + *(float *)(animConfig + 0x38); // +0x40: intercept (start + slope)
        return;
    case 2: // Mode 2: Noisy/randomized interpolation
        *(float *)(iVar2 + 0x3c) = DAT_00e2b1a4;
        *(undefined4 *)(iVar2 + 0x40) = 0;
        // Set additional parameters (likely thresholds or bias)
        *(float *)(iVar2 + 0x30) = *(float *)(animConfig + 0x3c) + fVar5;
        *(float *)(iVar2 + 0x34) = *(float *)(animConfig + 0x3c) + DAT_00e2b04c;
        *(float *)(iVar2 + 0x38) = *(float *)(animConfig + 0x3c) + DAT_00e445ac;
        if (0.0 < *(float *)(animConfig + 0x2c)) { // +0x2c: amplitude/noise scale
            fVar4 = *(float *)(animConfig + 0x2c) * DAT_00e2b334; // factor
            float param_1 = DAT_00e44850; // some starting value
            local_8 = 0.0;
            local_c = DAT_00e4458c;
            iVar3 = 0x15; // 21 iterations
            fVar5 = DAT_00e4458c;
            do {
                FUN_005006d0(); // generate random/noise value (might update param_1, local_c, etc.)
                if (param_1 < fVar5) {
                    param_1 = fVar5;
                }
                if (fVar5 < local_c) {
                    local_c = fVar5;
                }
                iVar3 = iVar3 + -1;
                fVar5 = local_8 + fVar4;
                local_8 = fVar5;
            } while (iVar3 != 0);
            // After noise sampling, compute final slope and intercept using min/max from noise
            fVar5 = (*(float *)(animConfig + 0x34) - *(float *)(animConfig + 0x38)) / (param_1 - local_c);
            *(float *)(iVar2 + 0x3c) = fVar5;
            *(float *)(iVar2 + 0x40) = *(float *)(animConfig + 0x38) - fVar5 * local_c;
            return;
        }
        break;
    case 4: // Mode 4: Use explicit range from config (time range)
        fVar5 = (*(float *)(animConfig + 0x34) - *(float *)(animConfig + 0x38)) /
                (*(float *)(animConfig + 0x40) - *(float *)(animConfig + 0x44));
        *(float *)(iVar2 + 0x3c) = fVar5;
        *(float *)(iVar2 + 0x40) = *(float *)(animConfig + 0x38) - fVar5 * *(float *)(animConfig + 0x44);
        return;
    case 5: // Mode 5: Direct assignment, no division
        *(float *)(iVar2 + 0x3c) = *(float *)(animConfig + 0x34) - *(float *)(animConfig + 0x38);
        *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)(animConfig + 0x38);
    }
    return;
}