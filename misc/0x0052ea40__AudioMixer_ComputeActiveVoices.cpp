// FUNC_NAME: AudioMixer_ComputeActiveVoices
uint AudioMixer_ComputeActiveVoices(void)
{
    int iVar1;
    byte bVar2;
    uint uVar3;
    float *pfVar4;
    uint uVar5;
    uint uVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float local_84;
    float local_80 [32];

    bVar2 = DAT_01219859; // total output channel count
    uVar3 = 0;
    // Reset selected outputs array (indices and weights)
    _DAT_0121930c = 0;
    _DAT_01219314 = 0;
    _DAT_0121931c = 0;
    _DAT_01219324 = 0;
    _DAT_0121932c = 0;
    _DAT_01219334 = 0;
    _DAT_0121933c = 0;
    DAT_01219344 = 0; // selected count

    if (DAT_01219859 == 0) {
        // No outputs, clear a flag and return
        DAT_01219390._4_4_ = DAT_01219390._4_4_ & 0xefffffff;
        return 0;
    }

    uVar5 = (uint)DAT_01219858; // total source count
    uVar6 = 0;
    local_84 = DAT_00e2eff4; // g_minVolumeThreshold
    if (uVar5 != 0) {
        pfVar4 = (float *)&DAT_01219398; // pointer to source data structure (6 floats per source)
        do {
            if (0x7f < uVar3) break; // safety bound (128 sources)
            // Check source flags: if mute flag set, bail out
            if (((uint)pfVar4[-1] & 0x10000000) != 0) {
                DAT_01219344 = 0;
                return 0;
            }
            if (-1 < *(int *)((int)&DAT_01219688 + uVar3)) {
                // Compute ratio for current volume / max volume
                if (*pfVar4 == 0.0) {
                    fVar7 = 0.0;
                } else {
                    fVar7 = *(float *)((int)&DAT_01219708 + uVar3) / *pfVar4;
                }
                // Compute ratio for peak volume / max peak
                if (*(float *)((int)&DAT_01219788 + uVar3) == 0.0) {
                    fVar9 = 0.0;
                } else {
                    fVar9 = *(float *)((int)&DAT_01219788 + uVar3) / pfVar4[1];
                }
                // Priority score = (1 - volumeRatio) * g_priorityFactor * peakRatio? Actually constants: g_normalizationFactor - volumeRatio
                fVar9 = (DAT_00e2b1a4 - fVar7) * pfVar4[-4] * fVar9;
                if (local_84 < fVar9) {
                    local_84 = fVar9; // track maximum priority
                }
                uVar6 = uVar6 + 1;
            }
            uVar3 = uVar3 + 4; // advance to next source (4-byte stride for parallel arrays)
            pfVar4 = pfVar4 + 6; // advance to next source data structure (6 floats = 0x18 bytes)
        } while (uVar6 < uVar5);
    }

    _memset(local_80, 0, 0x80); // clear per-channel accumulators (32 floats)

    fVar9 = DAT_00e2d7fc; // g_outputVolumeThreshold
    fVar7 = DAT_00e2b1a4; // g_normalizationFactor (1.0f)
    uVar3 = 0;
    fVar11 = 0.0;
    if (uVar5 != 0) {
        pfVar4 = (float *)&DAT_01219398;
        uVar6 = 0;
        do {
            if (0x7f < uVar6) break;
            if (-1 < *(int *)((int)&DAT_01219688 + uVar6)) {
                if (*pfVar4 == 0.0) {
                    fVar8 = 0.0;
                } else {
                    fVar8 = *(float *)((int)&DAT_01219708 + uVar6) / *pfVar4;
                }
                if (*(float *)((int)&DAT_01219788 + uVar6) == 0.0) {
                    fVar10 = 0.0;
                } else {
                    fVar10 = *(float *)((int)&DAT_01219788 + uVar6) / pfVar4[1];
                }
                // Priority score with additional factor
                fVar8 = pfVar4[-3] * (DAT_00e2b1a4 - fVar8) * pfVar4[-4] * fVar10;
                fVar11 = fVar8 + fVar11; // accumulate total priority
                // Add to per-channel accumulator (output channel index from DAT_01219688)
                local_80[*(int *)((int)&DAT_01219688 + uVar6)] =
                    local_80[*(int *)((int)&DAT_01219688 + uVar6)] + fVar8;
                uVar3 = uVar3 + 1;
            }
            uVar6 = uVar6 + 4;
            pfVar4 = pfVar4 + 6;
        } while (uVar3 < uVar5);

        // If total priority exceeds threshold, normalize and select outputs
        if (DAT_00e44598 < fVar11) {
            uVar3 = 0;
            fVar11 = DAT_00e2b1a4 / fVar11; // normalization factor
            if (bVar2 != 0) {
                pfVar4 = local_80;
                uVar5 = 0;
                do {
                    if (0xff < uVar5) break;
                    if (*(int *)((int)&DAT_0121982c + uVar5) != 0) {
                        fVar8 = *pfVar4 * fVar11;
                        *pfVar4 = fVar8;
                        // If normalized weight exceeds threshold, select this output
                        if (fVar9 < fVar8) {
                            (&DAT_0121930c)[DAT_01219344] = *(undefined4 *)((int)&DAT_01219828 + uVar5);
                            if (0.0 < fVar8) {
                                if (fVar7 <= fVar8) {
                                    fVar8 = fVar7; // clamp to 1.0
                                }
                            } else {
                                fVar8 = 0.0;
                            }
                            (&DAT_01219328)[DAT_01219344] = fVar8;
                            DAT_01219344 = DAT_01219344 + 1;
                        }
                        uVar3 = uVar3 + 1;
                    }
                    uVar5 = uVar5 + 8; // stride for output channel data (8 bytes per channel)
                    pfVar4 = pfVar4 + 1;
                } while (uVar3 < bVar2);
            }
            _DAT_01219324 = CONCAT44(DAT_01219328, local_84);
        }
    }

    // If the first selected weight is below threshold, clear selection
    if (_DAT_01219324 < DAT_00e2af44) {
        DAT_01219344 = 0;
    }

    uVar3 = DAT_01219344;
    if (DAT_01219344 != 0) {
        uVar5 = 0;
        do {
            uVar6 = (&DAT_0121930c)[uVar5]; // selected output index
            if ((uVar6 != 0xffffffff) && (uVar6 < 0x1000)) {
                iVar1 = uVar6 * 0x38; // voice structure stride
                // Check voice state (byte at offset 0) < 4 (inactive?)
                if ((&DAT_011a0f28 + iVar1 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar1] < 4)) {
                    // Set a flag on the voice's object (offset 0x1c)
                    if (*(int *)(&DAT_011a0f44 + iVar1) != 0) {
                        FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar1), 0x200000);
                        uVar3 = DAT_01219344;
                    }
                    // Update voice flags (offset 0x0c)
                    *(uint *)(&DAT_011a0f34 + iVar1) =
                        *(uint *)(&DAT_011a0f34 + iVar1) & 0xfcac8fff | 0x200000;
                    FUN_006189c0(); // refresh audio system
                }
            }
            uVar5 = uVar5 + 1;
        } while (uVar5 < uVar3);
    }

    return uVar3; // number of active outputs
}