// FUNC_NAME: Interpolator::advance(float deltaTime)
void __thiscall Interpolator::advance(float deltaTime) {
    // this is passed in ECX (shown as in_EAX in decompiled output)
    float normalizedDelta = deltaTime / *(float *)(this + 0x2C); // +0x2C: duration/scale factor

    switch (*(int *)(this + 0x28)) { // +0x28: interpolation mode
        case 1:
            // Simple call, possibly reset or linear mode
            FUN_00b99fcb(); // Could be "resetToZero" or similar
            return;
        case 2:
            // Calls a function with arguments from another structure pointed by ESI
            // ESI is likely a parent or controller object (set by caller)
            FUN_00535cd0(*(undefined4 *)(unaff_ESI + 8), *(undefined4 *)(unaff_ESI + 0xC));
            return;
        case 3:
            // Threshold check: does nothing if normalizedDelta is within certain bounds
            // Possibly a dead-zone or trigger condition
            if (DAT_00e2b198 < normalizedDelta) {
                return; // Above upper threshold
            }
            if (normalizedDelta <= DAT_00e2cd54) {
                return; // Below lower threshold
            }
            if (normalizedDelta <= DAT_00e35654) {
                return; // Middle threshold (no action)
            }
            return;
        case 4:
            // Linear interpolation with clamping
            {
                float val1 = *(float *)(this + 0x4C) * normalizedDelta + *(float *)(this + 0x48); // +0x48/+0x4C: slope/offset
                float val2 = *(float *)(this + 0x54) * normalizedDelta + *(float *)(this + 0x50); // +0x50/+0x54: slope/offset
                float result = (val1 < val2) ? val1 : val2; // Take minimum of the two lines

                // Clamp between min and max
                if (result < *(float *)(this + 0x44)) { // +0x44: min clamp
                    return;
                }
                if (*(float *)(this + 0x40) < result) { // +0x40: max clamp
                    return;
                }
                // No explicit assignment, result is discarded? This might be a bug in decompilation.
                // Possibly the result is stored back somewhere else.
                break;
            }
        case 5:
            // Modulo-based timing / waste cycles (likely a delay or synchronization)
            {
                int intPart = (int)*(float *)(this + 0x3C); // +0x3C: time value as integer
                if (*(float *)(this + 0x3C) <= 0.0f) {
                    intPart = -intPart; // Absolute value
                }
                // Simulate division by 8 with remainder (inefficient loop)
                int remainder = intPart;
                if (7 < intPart) {
                    int quotient = ((intPart - 8) >> 3) + 1; // (intPart - 8) / 8 + 1, but note unsigned shift?
                    int multiplied = quotient * 8;
                    // Loop to waste time (decrement quotient)
                    do {
                        quotient--;
                    } while (quotient != 0);
                    // Subtract the full multiples
                    intPart -= multiplied;
                    // Loop over the remainder (discarded)
                    do {
                        intPart--;
                    } while (intPart != 0);
                }
                // No effective computation; likely a timing delay
                return;
            }
        default:
            break;
    }
    return;
}