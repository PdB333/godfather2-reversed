// FUNC_NAME: PlayerController::processAnalogStick

// Function at 0x00955d30
// Processes analog stick input, applies deadzone, and computes a unit direction vector.
// this+0x70 is a bool flag indicating whether the stick input is active.
// Function calls getRawStickInput (0x00926810) to retrieve raw axis values.
// Uses global constants for deadzone thresholds, scale, and center.

extern void getRawStickInput(float *outX, float *outY);  // 0x00926810
extern char getExtraInputCondition();                    // 0x00956b70

extern float g_stickDeadzoneDefault;   // DAT_00d8c060
extern float g_stickDeadzoneAlt;       // DAT_00d8c064
extern float g_stickHalfRange;         // DAT_00d5780c (max raw value / 2)
extern float g_stickDeadzoneDivX;      // DAT_0120587c
extern float g_stickDeadzoneDivY;      // DAT_01205880
extern float g_stickCenter;            // DAT_00e44564
extern float g_stickScale;             // DAT_00d5eee4

void __thiscall PlayerController::processAnalogStick(float *outX, float *outY)
{
    float rawX, rawY;
    getRawStickInput(&rawX, &rawY);

    float deadzoneX = g_stickDeadzoneDefault;
    float deadzoneY = g_stickDeadzoneDefault;

    // +0x70: flag indicating alternative deadzone (e.g., when aiming)
    if (*(char *)(this + 0x70) != 0) {
        deadzoneX = g_stickDeadzoneAlt;
        deadzoneY = g_stickDeadzoneAlt;
    }

    bool haveInput = false;

    // Check X deadzone: outside center region → valid input
    if ((rawX < deadzoneX / g_stickDeadzoneDivX) ||
        (g_stickHalfRange - deadzoneX / g_stickDeadzoneDivX < rawX)) {
        haveInput = true;
    }

    // Check Y deadzone
    if ((rawY < deadzoneY / g_stickDeadzoneDivY) ||
        (g_stickHalfRange - deadzoneY / g_stickDeadzoneDivY < rawY)) {
        // Also require extra condition (e.g., button pressed)
        char extra = getExtraInputCondition();
        if (extra != 0) {
            haveInput = true;
        }
    } else {
        // Y inside deadzone – if X also has no input, clear and return
        if (!haveInput) {
            *outX = 0.0f;
            *outY = 0.0f;
            *(char *)(this + 0x70) = 0; // clear active flag
            return;
        }
    }

    // Compute centered coordinates and normalize to unit direction
    float dx = g_stickCenter - (rawX * g_stickScale - g_stickHalfRange);
    float dy = g_stickCenter - (rawY * g_stickScale - g_stickHalfRange);

    *outX = dx;
    *outY = dy;

    // Normalize using halfRange / length (non‑standard but matching original)
    float invMag = g_stickHalfRange / sqrtf(dx * dx + dy * dy);
    *outX *= invMag;
    *outY *= invMag;

    *(char *)(this + 0x70) = 1; // set active flag
    return;
}