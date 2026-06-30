// FUNC_NAME: TimeAdjuster::adjustOffset
int __fastcall TimeAdjuster::adjustOffset(int this)
{
    // Combine two offset fields: +0xCC (204) and +0xC8 (200)
    int baseValue = *(int *)(this + 0xCC) + *(int *)(this + 200);

    // Call an update routine with the value at +0x40 (likely a state or parameter)
    FUN_008c74d0(*(undefined4 *)(this + 0x40));

    // Compute unsigned time delta between +0x68 and +0x6c (timestamps)
    uint currentTime = *(uint *)(this + 0x68);
    uint lastTime    = *(uint *)(this + 0x6c);
    int timeDiff;
    if (lastTime < currentTime) {
        timeDiff = currentTime - lastTime; // No wrap
    } else {
        timeDiff = 0; // No elapsed time or wrap, treat as zero
    }

    // Get scaling factor (e.g., speed or delta time multiplier)
    double scaleFactor = FUN_008bd4b0(); // Returns time-related value

    // Convert timeDiff to float, handling potential unsigned wrap (if timeDiff is negative)
    double timeDiffFloat = (double)timeDiff;
    if (timeDiff < 0) {
        // Adjust for 32-bit unsigned wrap: add 2^32
        const double kTwoPower32 = 4294967296.0; // 2^32
        timeDiffFloat += kTwoPower32;
    }

    // Compute negative product: -(timeDiffFloat * scaleFactor)
    double adjustment = -(timeDiffFloat * scaleFactor);
    float adjustmentFloat = (float)adjustment;

    // Apply adjustment to baseValue
    if ((double)0.0 < adjustment) {
        // Positive adjustment: add directly
        return baseValue + (int)adjustment;
    }
    if (adjustmentFloat < 0.0f) {
        // Floor toward negative infinity if fractional
        if (adjustmentFloat != (float)(int)adjustment) {
            adjustmentFloat = (float)((int)adjustment - 1);
        }
        baseValue += (int)adjustmentFloat;
    }
    return baseValue;
}