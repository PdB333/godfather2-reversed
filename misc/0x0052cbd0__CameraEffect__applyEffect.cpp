// FUNC_NAME: CameraEffect::applyEffect
void CameraEffect::applyEffect(Vector4* position, float intensity, float duration, bool isAdditive, int someFlag, Vector4* customVector, float falloffStart, float falloffEnd)
{
    uint currentEffectId;
    uint prevEffectId;

    // Get current effect ID from global or from object at DAT_012054dc + 0x16c
    if (DAT_012054dc == 0) {
        currentEffectId = DAT_012058a4;
    } else {
        currentEffectId = *(uint *)(DAT_012054dc + 0x16c);
    }

    // Increment global effect counter
    _DAT_01205500 = _DAT_01205500 + 1;

    // Clamp effect parameters to valid ranges
    if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
    if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
    _DAT_011f3a30 = 1;

    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 0;

    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = 0;

    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 5;

    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;

    // Set effect flag
    FUN_00609890(1);

    // Check if effect ID is valid and process
    uint effectId = DAT_012058a4;
    if (DAT_012054dc != 0) {
        effectId = *(uint *)(DAT_012054dc + 0x16c);
    }
    if ((effectId != 0xffffffff) && (effectId < 0x1000)) {
        int offset = effectId * 0x38;
        if ((&DAT_011a0f28 + offset != (byte *)0x0) && ((byte)(&DAT_011a0f28)[offset] < 4)) {
            if (*(int *)(&DAT_011a0f44 + offset) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + offset), 0x100000);
            }
            *(uint *)(&DAT_011a0f34 + offset) = *(uint *)(&DAT_011a0f34 + offset) & 0xfc9c8fff | 0x100000;
            FUN_006189c0();
        }
    }

    // Set render state
    FUN_00417cf0(1, 2, 1);

    // Clamp again
    if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
    if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
    _DAT_01125d94 = DAT_01125e84;
    _DAT_01125d90 = DAT_01219908;
    _DAT_01126028 = 0;
    _DAT_011f3a44 = 0;

    // Store position
    _DAT_01125e30 = *position;
    uRam01125e34 = position[1];
    uRam01125e38 = position[2];
    uRam01125e3c = position[3];

    // Update camera
    FUN_0053d590();

    if (isAdditive == false) {
        // Non-additive mode
        FUN_0052be20(intensity, 0, someFlag);
        FUN_0053d590();
        FUN_004e3a70();

        float adjustedDuration = duration;
        float baseIntensity = DAT_00e35654;
        float baseDuration = DAT_00e2d99c;
        if ((char)someFlag != '\0') {
            baseIntensity = DAT_00e2cd54;
            baseDuration = DAT_00e2b04c;
        }

        if (intensity < baseDuration) {
            adjustedDuration = intensity * baseIntensity * duration;
        }

        if (customVector == (Vector4 *)0x0) {
            // No custom vector
            if (DAT_00e2b1a4 <= adjustedDuration) {
                FUN_00417cf0(1, 2, 1);
            } else {
                FUN_00417fe0();
                adjustedDuration = (float)(int)(adjustedDuration * DAT_00e44584);
                FUN_00417f00(adjustedDuration, adjustedDuration, adjustedDuration, adjustedDuration);
                FUN_00417cf0(1, 0xe, 0xf);
            }
            _DAT_01126028 = 0;
            _DAT_01125d90 = DAT_01219908;
            _DAT_01125d94 = DAT_01125e84;
        } else {
            // Custom vector provided
            _DAT_01125d94 = DAT_01125ee4;
            _DAT_01126028 = 3;
            _DAT_01125d90 = DAT_01219908;

            if ((falloffStart == 0.0f) && (falloffEnd == 0.0f)) {
                falloffStart = DAT_00e2d99c;
                falloffEnd = DAT_00e445ac;
            }
            _DAT_01125e48 = falloffStart * DAT_00e2cd54;
            _DAT_01125e4c = falloffEnd * DAT_00e2cd54;

            if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
            if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
            _DAT_011f3a44 = 1;

            FUN_00417cf0(1, 5, 6);

            uint effectHandle = DAT_012058a8;
            int objPtr = DAT_012054dc;
            _DAT_01125e44 = adjustedDuration;

            uint handle2 = DAT_012058a8;
            if (DAT_012054dc != 0) {
                handle2 = *(uint *)(DAT_012054dc + 0x170);
            }
            FUN_00606e60(handle2, 0x210000);

            if (objPtr != 0) {
                effectHandle = *(uint *)(objPtr + 0x170);
            }

            // Store custom vector
            _DAT_01125e50 = *customVector;
            uRam01125e54 = customVector[1];
            uRam01125e58 = customVector[2];
            uRam01125e5c = customVector[3];
            _DAT_01125e64 = effectHandle;
        }

        // Finalize effect
        FUN_0053d310();

        // Allocate and fill effect buffer (8 floats)
        float* effectBuffer = (float*)FUN_0060cd00(0xd, 4, 0, 1, 0);
        float val1 = DAT_00e2eff4;
        float val2 = DAT_00e2b1a4;
        if (effectBuffer != (float*)0x0) {
            effectBuffer[0] = DAT_00e2eff4;
            effectBuffer[1] = val1;
            effectBuffer[2] = val2;
            effectBuffer[3] = val1;
            effectBuffer[4] = val2;
            effectBuffer[5] = val2;
            effectBuffer[6] = val1;
            effectBuffer[7] = val2;
            FUN_0060cde0();
        }
        FUN_00612e00();
    }

    // Reset effect state
    FUN_00606470();

    // Clamp again
    if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
    if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
    _DAT_011f3a30 = 1;

    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = 1;

    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 7;

    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;

    FUN_00417cf0(1, 5, 6);

    if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
    if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
    _DAT_011f3a44 = 0;

    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 1;

    // Check if effect ID changed; if not, decrement counter
    uint newEffectId = DAT_012058a4;
    if (DAT_012054dc != 0) {
        newEffectId = *(uint *)(DAT_012054dc + 0x16c);
    }
    if (prevEffectId == newEffectId) {
        _DAT_01205500 = _DAT_01205500 - 1;
    }
}