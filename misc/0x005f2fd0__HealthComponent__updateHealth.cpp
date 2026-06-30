// FUNC_NAME: HealthComponent::updateHealth
void __thiscall HealthComponent::updateHealth(float delta) {
    float maxValue = DAT_00e2d99c;                  // global max health (e.g., 1.0f)
    if (this != nullptr) {
        // Check a condition based on a masked value at offset +0x58
        // The AND operation interprets the float as a uint, possibly to ignore sign or exponent bits
        float maskedValue = reinterpret_cast<float>(
            reinterpret_cast<uint32_t>(*(float*)(this + 0x58)) & DAT_00e44680
        );
        if (DAT_00e44598 < maskedValue) {
            // Compute new health: delta * multiplier * factor + current
            float newValue = delta * DAT_00e2b050 * *(float*)(this + 0x58) + *(float*)(this + 0x54);
            // Clamp to [0.0, maxValue]
            if (newValue > 0.0f) {
                if (newValue > maxValue)
                    newValue = maxValue;
            } else {
                newValue = 0.0f;
            }
            *(float*)(this + 0x54) = newValue;          // +0x54: current health
            if (newValue == 0.0f || newValue == maxValue) {
                // Trigger callback when health reaches min or max
                // Arguments: byte at +0x64 (type?), int32 at +0x5c (ID?), byte at +0x65 (flags?)
                FUN_005dbc10(*(uint8_t*)(this + 0x64), *(uint32_t*)(this + 0x5c), *(uint8_t*)(this + 0x65));
                FUN_005f3640();                          // e.g., notify state change
                *(uint8_t*)(this + 0x67) = 0xff;         // +0x67: mark as dead/done
            }
        }
    }
}