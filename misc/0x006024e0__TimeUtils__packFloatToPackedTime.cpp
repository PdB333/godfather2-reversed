// FUNC_NAME: TimeUtils::packFloatToPackedTime
uint TimeUtils::packFloatToPackedTime(void)
{
    // Global constants (likely frame rate and rounding offset)
    // DAT_00e2b1a4: some threshold (maybe max sub-frame value)
    // DAT_00e2eff4: another threshold (min sub-frame value)
    // DAT_00e4466c: frame rate multiplier (e.g., 30.0f)
    // DAT_00e2cd54: rounding constant (0.5f)
    // DAT_00e44668: another multiplier (maybe for sub-frame scaling)
    // DAT_00e2a848: max value for sub-frame (e.g., 1.0f)

    float local_1c = DAT_00e2b1a4;          // +0x00 (local)
    float local_18;                         // +0x04 (local) – will be overwritten
    float local_10[3];                      // +0x08 (local array)

    // Get a random or time-based float (e.g., from a noise function)
    float fVar4 = (float)FUN_00b9a660();    // returns float10 (80-bit), cast to float

    local_10[0] = 0.0f;

    // Compute integer frame count from fVar4
    longlong lVar1 = (longlong)ROUND(fVar4 * DAT_00e4466c + DAT_00e2cd54);
    local_18 = (float)lVar1;
    float fVar2 = local_18;

    // Check if frame count is non-zero and not a sentinel value (5.73832e-42)
    if ((local_18 != 0.0f) && (local_18 != 5.73832e-42f)) {
        // Store high 32 bits of lVar1 (unused? maybe for global state)
        // _local_18 is a global variable overlapping local_18? The decompiler shows it.
        // This likely updates a global with the high part of the frame count.
        // uStack_14 = (undefined4)((ulonglong)lVar1 >> 0x20);
        // _local_18 = CONCAT44(uStack_14, DAT_00e2b1a4); // modifies global

        local_1c = DAT_00e2eff4;            // reset local_1c to min threshold
        double dVar5 = (double)fVar4;       // convert to double for division
        local_10[0] = fVar4;                // store original float

        // Call some function that might modify EDI (unaff_EDI)
        FUN_00b99fcb();

        // After call, unaff_EDI points to some data; divide first element by dVar5
        local_10[0] = *unaff_EDI / (float)dVar5;

        // Clamp local_10[0] between DAT_00e2eff4 and DAT_00e2b1a4
        if (local_10[0] <= DAT_00e2b1a4) {
            float* pfVar3 = &local_1c;
            if (DAT_00e2eff4 <= local_10[0]) {
                pfVar3 = local_10;
            }
        }
        else {
            float* pfVar3 = &local_18;      // use frame count if above max
        }

        // Convert selected value to double and call another function
        dVar5 = (double)*pfVar3;
        FUN_00b9b988();

        local_1c = (float)dVar5;

        // If unaff_EDI[2] is negative (and non-zero), invert sub-frame
        if ((unaff_EDI[2] <= 0.0f) && (unaff_EDI[2] != 0.0f)) {
            local_1c = DAT_00e2a848 - local_1c;
        }

        // Compute final sub-frame value with rounding
        local_10[0] = (float)(longlong)ROUND(local_1c * DAT_00e44668 + DAT_00e2cd54);
    }

    // Pack: lower 12 bits = frame count (fVar2), upper 20 bits = sub-frame (local_10[0])
    return ((int)local_10[0] << 12) | (uint)fVar2;
}