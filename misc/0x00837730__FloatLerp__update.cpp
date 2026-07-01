// FUNC_NAME: FloatLerp::update

void __thiscall FloatLerp::update(uint thisPtr) {
    float local_10;
    float *pLocalFloat;
    int local_c;
    uint local_4;

    // Clear bit 0 of flags at +0x84
    *(ushort *)(thisPtr + 0x84) = *(ushort *)(thisPtr + 0x84) & 0xfffe;

    if (*(int *)(thisPtr + 0xd8) == 0) {
        // If the lerp is not active, initialize
        FloatLerp::initialize();           // FUN_00837020
        FloatLerp::setup();                // FUN_008370e0
        *(float *)(thisPtr + 0xb4) = 0.0f; // currentValue = 0

        local_10 = *(float *)(thisPtr + 0xac); // duration
        pLocalFloat = &local_10;
        local_c = g_EventIdStart;           // DAT_0112dbe0
        local_4 = 0;
        Func_00408a00(&local_c, 0);         // dispatch start event

        // Set bit 2 in flags
        *(ushort *)(thisPtr + 0x84) = *(ushort *)(thisPtr + 0x84) | 4;

        local_c = g_EventIdUpdate;          // DAT_0112dbd8
        local_4 = 0;
        pLocalFloat = (float *)(thisPtr + 0xac); // duration
        Func_00408a00(&local_c, 0);         // dispatch update event with duration
    } else {
        // Lerp is active: update current value
        local_10 = *(float *)(thisPtr + 0xb4);   // currentValue
        float fVar1 = *(float *)(thisPtr + 0xb0) - local_10; // target - current
        if (fVar1 <= *(float *)(thisPtr + 0xac)) { // if remaining <= duration
            *(float *)(thisPtr + 0xb4) = fVar1;   // current = remaining
            local_10 = (*(float *)(thisPtr + 0xac) - *(float *)(thisPtr + 0xb0)) + local_10; // new duration? overflow?
            FloatLerp::onLerpReachedTarget(local_10); // FUN_008366c0
            pLocalFloat = &local_10;
            local_c = g_EventIdUpdate;          // DAT_0112dbd8
            local_4 = 0;
            Func_00408a00(&local_c, 0);         // dispatch update event
        }
    }

    // Reset target value to global default
    *(float *)(thisPtr + 0xb0) = g_DefaultTarget; // DAT_00d73c70
    return;
}