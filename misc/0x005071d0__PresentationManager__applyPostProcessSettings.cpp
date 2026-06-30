// FUNC_NAME: PresentationManager::applyPostProcessSettings
// Address: 0x005071d0
// This function applies post-processing effect settings, clamping quality levels and updating global state.
// It takes a vector/color (param_1), multiple unknown parameters, and a boolean flag (param_10).
// Based on the object state and globals, it adjusts rendering quality parameters.

void PresentationManager::applyPostProcessSettings(
    const float* color,        // param_1: pointer to 4 floats (likely RGBA)
    int param2,                // param_2
    int param3,                // param_3
    int param6,                // param_6
    int param7,                // param_7
    int param8,                // param_8
    int param9,                // param_9 (unused)
    bool enableEffect          // param_10: flag to enable/disable effect
)
{
    // Check if this object is either null (first byte 0) or the effect is not yet applied (offset +0x1e from inner struct)
    if ((*reinterpret_cast<const char*>(this) == '\0') ||
        (*(reinterpret_cast<const char*>(*reinterpret_cast<int*>(reinterpret_cast<const char*>(this) + 4) + 0x1e) != '\0')))
    {
        // Store some global pointers (probably objects)
        // DAT_0121a204 = DAT_0121a36c;  // likely a pointer to some resource
        // DAT_0121a200 = DAT_0121a368;  // another resource
        if (DAT_012058e8 == &DAT_0121a1f0)   // comparison to a global instance
        {
            FUN_0060a460(DAT_0121a36c);  // release or decrement ref count
            FUN_0060a460(DAT_0121a200);
        }

        // Branch based on a global flag (DAT_0120575b)
        if (DAT_0120575b == '\0')
        {
            if (*reinterpret_cast<const char*>(this) == '\0')
                _DAT_0121a300 = 0;   // set global to 0
            else
                _DAT_0121a300 = *reinterpret_cast<int*>(*reinterpret_cast<int*>(this + 4) + 0x24);  // offset 0x24
        }
        else
        {
            FUN_00536990();  // some setup function
            if (*reinterpret_cast<const char*>(this) == '\0')
                FUN_00536a40(0, param_4, param_5, 1.0f);  // call with 0 and 1.0
            else
            {
                // Compute float: byte at offset 0x1d from inner struct, multiplied by constants
                float factor = (static_cast<float>(*reinterpret_cast<const unsigned char*>(*reinterpret_cast<int*>(this + 4) + 0x1d)) + DAT_00e2cd54) * DAT_00e2ee80;
                FUN_00536a40(factor, param_4, param_5, 0.0f);
            }
        }

        // Clamp quality level for index 0x19 (25)
        if (DAT_012058d0 < 0x19)   // minimum level
            DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988)   // maximum level
            DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;         // setting for slot 0x3c (60)

        // Clamp for index 0x18 (24)
        if (DAT_012058d0 < 0x18)
            DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988)
            DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;         // setting for slot 0x38 (56)

        // Clamp for index 0xf (15)
        if (DAT_012058d0 < 0xf)
            DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988)
            DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;         // setting for slot 0x14 (20)

        // Clamp for index 0xe (14)
        if (DAT_012058d0 < 0xe)
            DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988)
            DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 0;         // setting for slot 0x10 (16)

        // Clamp for index 0x1b (27)
        if (DAT_012058d0 < 0x1b)
            DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988)   // note: uses 0x1a for max
            DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 1;         // setting for slot 0x44 (68)

        FUN_004ec7a0();  // unknown

        // Clamp for index 0x16 (22)
        if (DAT_012058d0 < 0x16)
            DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988)
            DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;         // setting for slot 0x30 (48)

        FUN_005368e0();  // unknown

        // Copy color (param_1) into global array
        _DAT_0121a2b0 = color[0];
        _DAT_0121a2b4 = color[1];
        _DAT_0121a2b8 = color[2];
        _DAT_0121a2bc = color[3];

        // If global pointer matches and another condition, apply the color to something
        if ((DAT_012058e8 == &DAT_0121a1f0) && (DAT_0121a200 == DAT_0121a368))
        {
            FUN_0060add0(DAT_0121a368, DAT_0121a31c, &DAT_0121a2b0);  // likely sets color on object
        }

        FUN_00536550();  // unknown

        if (enableEffect == false)
            FUN_00506e40(param2, param3, param6, param7, param8);  // disable variant
        else
            FUN_00506fa0();  // enable variant

        FUN_00612e00();  // unknown

        // Reset some global vector
        _DAT_0121a310 = 0;
        _DAT_0121a314 = 0;
        _DAT_0121a318 = 0;

        // Repeat clamping and setting with different values (second pass)
        // Clamp for index 0x19 (25)
        if (DAT_012058d0 < 0x19)
            DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988)
            DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;

        // Clamp for index 0x18 (24)
        if (DAT_012058d0 < 0x18)
            DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988)
            DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;

        // Clamp for index 0xf (15)
        if (DAT_012058d0 < 0xf)
            DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988)
            DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;

        // Clamp for index 0xe (14)
        if (DAT_012058d0 < 0xe)
            DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988)
            DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 1;   // changed from 0 to 1 compared to first pass

        // Clamp for index 0x1b (27)
        if (DAT_012058d0 < 0x1b)
            DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988)
            DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 0;   // changed from 1 to 0

        FUN_00417cf0(1, 5, 6);  // finalize with three parameters

        // Clamp for index 0x16 (22)
        if (DAT_012058d0 < 0x16)
            DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988)
            DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
    }
    return;
}