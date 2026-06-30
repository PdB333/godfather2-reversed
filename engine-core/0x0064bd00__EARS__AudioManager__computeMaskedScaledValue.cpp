// FUNC_NAME: EARS::AudioManager::computeMaskedScaledValue
void __thiscall EARS::AudioManager::computeMaskedScaledValue(byte shift, float scale) {
    // Compute (2^shift - 1) * scale, round to integer, then convert back to float
    int result = (int)round(((1 << (shift & 0x1f)) - 1) * scale);
    float value = static_cast<float>(result);
    // Apply the computed value via internal function
    FUN_0064b810(shift, &value);
}