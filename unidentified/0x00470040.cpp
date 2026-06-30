// FUN_00470040: Interpolator::update
float Interpolator::update(float target, uint32_t flags, void* userData)
{
    // Default context if none provided
    if (userData == nullptr) {
        userData = g_defaultContext; // &DAT_00e2e358
    }

    // Compute a smoothed/processed value from target and flags
    float smoothed = computeSmoothedValue(target, flags); // FUN_004700a0

    // If the smoothed value is not zero (sentinel constant at 0x00e2b05c), invoke callback
    if (smoothed != 0.0f) { // DAT_00e2b05c is 0.0f
        (this->*vtable[0x60])(userData, smoothed); // virtual onValueChanged (+0x60)
    }

    // Return the original target unchanged
    return target;
}