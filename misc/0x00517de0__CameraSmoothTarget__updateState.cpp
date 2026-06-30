// FUNC_NAME: CameraSmoothTarget::updateState
// Address: 0x00517de0
// Role: Updates camera smoothing target state, copies current to desired if transition is not active, then resets current to defaults.

struct CameraSmoothTarget {
    // Current state (0x01219250 - 0x012192a0)
    float m_currentScale;          // +0x00
    float m_currentOffset;         // +0x04
    float m_currentRotation;       // +0x08
    int32_t m_currentInt1;         // +0x0C
    int32_t m_currentInt2;         // +0x10
    int32_t m_currentInt3;         // +0x14
    int32_t m_currentInt4;         // +0x18
    int32_t m_currentInt5;         // +0x1C
    float m_currentFloat1;         // +0x20
    float m_currentFloat2;         // +0x24
    float m_currentFloat3;         // +0x28
    float m_currentTime;           // +0x2C
    int32_t m_currentFlag1;        // +0x30
    int32_t m_currentFlag2;        // +0x34
    float m_currentThreshold1;     // +0x38
    float m_currentThreshold2;     // +0x3C
    int32_t m_currentInt6;         // +0x40
    int32_t m_currentInt7;         // +0x44
    uint32_t m_currentUint1;       // +0x48
    uint32_t m_currentUint2;       // +0x4C
    float m_currentTriggerZero;    // +0x50

    // Desired state (0x012192b0 - 0x012192fc)
    float m_desiredScale;          // +0x60
    float m_desiredOffset;         // +0x64
    float m_desiredRotation;       // +0x68
    int32_t m_desiredInt1;         // +0x6C
    int32_t m_desiredInt2;         // +0x70
    int32_t m_desiredInt3;         // +0x74
    int32_t m_desiredInt4;         // +0x78
    int32_t m_desiredInt5;         // +0x7C
    float m_desiredFloat1;         // +0x80
    float m_desiredFloat2;         // +0x84
    float m_desiredFloat3;         // +0x88
    float m_desiredTime;           // +0x8C
    int32_t m_desiredFlag1;        // +0x90
    int32_t m_desiredFlag2;        // +0x94
    float m_desiredThreshold1;     // +0x98
    float m_desiredThreshold2;     // +0x9C
    int32_t m_desiredInt6;         // +0xA0
    int32_t m_desiredInt7;         // +0xA4
    uint32_t m_desiredUint1;       // +0xA8
    uint32_t m_desiredUint2;       // +0xAC
};

// Global instance at 0x01219250
extern CameraSmoothTarget gCameraSmoothTarget;

// Constants
extern float gMinTimeThreshold;         // 0x00e2af44
extern float gDefaultFloat;             // 0x00e39f98
extern int32_t gDefaultInt;             // 0x00e2b1a4
extern float gClearTime;                // 0x00e445ac

// Sub-functions
char __thiscall isTransitionActive(void); // FUN_00517040
void __thiscall finishStateUpdate(void); // FUN_00517d50

void __thiscall CameraSmoothTarget::updateState(void)
{
    char updateResult;

    // Check if we should reset desired time
    if ((gCameraSmoothTarget.m_currentTriggerZero == 0.0f) ||
        (gCameraSmoothTarget.m_currentTime < gMinTimeThreshold) ||
        ((gCameraSmoothTarget.m_currentThreshold1 < gMinTimeThreshold &&
          gCameraSmoothTarget.m_currentThreshold2 < gMinTimeThreshold)))
    {
        gCameraSmoothTarget.m_desiredTime = 0.0f;
    }
    else
    {
        updateResult = isTransitionActive();
        if (updateResult == '\0')
        {
            // Copy current state to desired (20 fields)
            gCameraSmoothTarget.m_desiredScale = gCameraSmoothTarget.m_currentScale;
            gCameraSmoothTarget.m_desiredOffset = gCameraSmoothTarget.m_currentOffset;
            gCameraSmoothTarget.m_desiredRotation = gCameraSmoothTarget.m_currentRotation;
            gCameraSmoothTarget.m_desiredInt1 = gCameraSmoothTarget.m_currentInt1;
            gCameraSmoothTarget.m_desiredInt2 = gCameraSmoothTarget.m_currentInt2;
            gCameraSmoothTarget.m_desiredInt3 = gCameraSmoothTarget.m_currentInt3;
            gCameraSmoothTarget.m_desiredInt4 = gCameraSmoothTarget.m_currentInt4;
            gCameraSmoothTarget.m_desiredInt5 = gCameraSmoothTarget.m_currentInt5;
            gCameraSmoothTarget.m_desiredFloat1 = gCameraSmoothTarget.m_currentFloat1;
            gCameraSmoothTarget.m_desiredFloat2 = gCameraSmoothTarget.m_currentFloat2;
            gCameraSmoothTarget.m_desiredFloat3 = gCameraSmoothTarget.m_currentFloat3;
            gCameraSmoothTarget.m_desiredTime = gCameraSmoothTarget.m_currentTime;
            gCameraSmoothTarget.m_desiredFlag1 = gCameraSmoothTarget.m_currentFlag1;
            gCameraSmoothTarget.m_desiredFlag2 = gCameraSmoothTarget.m_currentFlag2;
            gCameraSmoothTarget.m_desiredThreshold1 = gCameraSmoothTarget.m_currentThreshold1;
            gCameraSmoothTarget.m_desiredThreshold2 = gCameraSmoothTarget.m_currentThreshold2;
            gCameraSmoothTarget.m_desiredInt6 = gCameraSmoothTarget.m_currentInt6;
            gCameraSmoothTarget.m_desiredInt7 = gCameraSmoothTarget.m_currentInt7;
            gCameraSmoothTarget.m_desiredUint1 = gCameraSmoothTarget.m_currentUint1;
            gCameraSmoothTarget.m_desiredUint2 = gCameraSmoothTarget.m_currentUint2;
        }
    }

    // Reset current state to default values
    gCameraSmoothTarget.m_currentFloat1 = gDefaultFloat;   // +0x20
    gCameraSmoothTarget.m_currentFloat2 = gDefaultFloat;   // +0x24
    gCameraSmoothTarget.m_currentInt2 = 0;                 // +0x10
    gCameraSmoothTarget.m_currentInt3 = 0;                 // +0x14
    gCameraSmoothTarget.m_currentInt4 = 0;                 // +0x18
    gCameraSmoothTarget.m_currentInt5 = gDefaultInt;       // +0x1C
    gCameraSmoothTarget.m_currentScale = (float)gDefaultInt;  // +0x00 (float conversion)
    gCameraSmoothTarget.m_currentOffset = (float)gDefaultInt; // +0x04
    gCameraSmoothTarget.m_currentRotation = (float)gDefaultInt; // +0x08
    gCameraSmoothTarget.m_currentFloat3 = gClearTime;      // +0x28
    gCameraSmoothTarget.m_currentTime = 0.0f;              // +0x2C
    gCameraSmoothTarget.m_currentInt6 = 0;                 // +0x40
    gCameraSmoothTarget.m_currentInt7 = 0;                 // +0x44
    gCameraSmoothTarget.m_currentFlag1 = 0;                // +0x30
    gCameraSmoothTarget.m_currentFlag2 = 0;                // +0x34
    gCameraSmoothTarget.m_currentThreshold1 = (float)gDefaultInt; // +0x38
    gCameraSmoothTarget.m_currentThreshold2 = (float)gDefaultInt; // +0x3C
    gCameraSmoothTarget.m_currentInt1 = 0;                 // +0x0C
    gCameraSmoothTarget.m_currentTriggerZero = 0.0f;       // +0x50

    finishStateUpdate();
    return;
}