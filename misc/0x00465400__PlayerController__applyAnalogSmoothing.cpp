// FUNC_NAME: PlayerController::applyAnalogSmoothing
void __thiscall PlayerController::applyAnalogSmoothing(float* value, float sensitivity)
{
    // Sentinel value to use the object's own sensitivity (stored at offset 0x1694)
    const float kSensitivitySentinel = DAT_00e2eff4; // likely -1.0f
    const float kMaxInput = DAT_00e44564;            // +?? maximum allowed input magnitude (e.g., 1.0)
    const float kDivisorBase = DAT_00e2b1a4;         // +?? base for scaling divisor (e.g., 1.0)

    if (sensitivity == kSensitivitySentinel)
    {
        sensitivity = *(float*)((char*)this + 0x1694); // +0x1694: customSensitivity
    }

    float fVar1 = *value;
    float threshold = kMaxInput - sensitivity; // threshold for dead zone

    if (threshold <= fVar1)
    {
        if (fVar1 <= sensitivity)
        {
            *value = 0.0f; // inside dead zone → zero
            return;
        }
        fVar1 = fVar1 - sensitivity; // above dead zone → reduce by sensitivity
    }
    else
    {
        fVar1 = fVar1 + sensitivity; // below negative dead zone → increase by sensitivity
    }

    // Normalize to the range (-1, 1) after dead zone removal
    *value = fVar1 / (kDivisorBase - sensitivity);
}