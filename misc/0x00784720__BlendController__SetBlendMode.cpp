// FUNC_NAME: BlendController::SetBlendMode
void __thiscall BlendController::SetBlendMode(bool isSecondMode)
{
    // Select source value based on mode
    // +0x64 (100) = first source value, +0x68 (104) = second source value
    uint32_t sourceValue = isSecondMode ? *(uint32_t*)((uint8_t*)this + 0x68) : *(uint32_t*)((uint8_t*)this + 0x64);

    // Store selected value to target field at +0x80 (128)
    *(uint32_t*)((uint8_t*)this + 0x80) = sourceValue;

    // Compute and store blend value: first source + constant
    // +0x7c (124) = blend value, DAT_01205228 = global constant (likely a delta time or speed)
    *(float*)((uint8_t*)this + 0x7c) = *(float*)((uint8_t*)this + 0x64) + DAT_01205228;
}