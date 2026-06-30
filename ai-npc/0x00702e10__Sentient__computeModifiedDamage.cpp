// FUNC_NAME: Sentient::computeModifiedDamage
// Function at 0x00702e10 - Computes a modified damage value with random variation and probability check.
// Uses member fields at offsets +0x504 and +0x508 (likely min/max damage modifiers).
float __thiscall Sentient::computeModifiedDamage(float input) {
    float localValue = input;

    // Apply probability check; may modify localValue based on internal settings.
    if (applyProbabilityCheck(&localValue)) {
        // Interpolate between two member values using localValue as blend factor.
        localValue = (1.0f - localValue) * this->field_0x508 + this->field_0x504 * localValue;
        // Scale by random 0..1 for variation.
        localValue *= getRandomFloat01();
        return localValue;
    }
    return 0.0f;
}