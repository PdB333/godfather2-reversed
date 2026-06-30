// FUNC_NAME: PlayerSM::updateAbilityTimer
void __thiscall PlayerSM::updateAbilityTimer(int thisPtr)
{
    float deltaTime = DAT_012067e8; // Frame delta time

    // Update first timer (cooldown?) at +0x188
    if (_DAT_00d577a0 < *(float *)(thisPtr + 0x188)) {
        *(float *)(thisPtr + 0x188) -= DAT_012067e8;
    }

    // Check flag at +0x2b4 bit 1 (ability active flag)
    if ((*(byte *)(thisPtr + 0x2b4) & 0x02) != 0) {
        int state = FUN_006b4860(); // Get global state (maybe player state machine)
        if (state != 4 && state != 3) {
            // Invalid state: clear the flag and exit
            *(byte *)(thisPtr + 0x2b4) &= 0xFD;
            return;
        }

        // Decrement active duration timer at +0x18c
        float activeTimer = *(float *)(thisPtr + 0x18c) - deltaTime;
        *(float *)(thisPtr + 0x18c) = activeTimer;
        if (activeTimer <= 0.0f) {
            // Timer expired: reset and trigger event/hash
            *(float *)(thisPtr + 0x18c) = _DAT_00d5780c; // Reset to default duration
            FUN_006ada80(thisPtr, 0x4E76981C); // Play sound/event (hash for "ability_end" or similar)

            // Debug string formatting
            struct StringBuffer {
                int *data; // likely pointer to string data
                int *field_4;
                undefined field_8;
            } buffer;
            buffer.field_4 = local_24; // local_24 is a small buffer (8 bytes)
            buffer.data = DAT_0112ad8c; // Some global string prefix
            buffer.field_8 = 0;
            FUN_00408a00(&buffer, 0);   // Format string? (used for debug output)

            if (local_1c[0] != 0) {
                FUN_004daf90(local_1c); // Cleanup string object (likely EA::Std::string destructor)
            }
        }
    }
}