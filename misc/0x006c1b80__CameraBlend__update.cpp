// FUNC_NAME: CameraBlend::update
class CameraBlend {
public:
    // Offsets: +0x10 currentQuat (quat x,y,z,w)
    // +0x30 field_0x30 (char)
    // +0x34 field_0x34 (int)
    // +0x38 field_0x38 (char)
    // +0x3a isBlending (char)
    // +0x3b previousEnable (char)
    // +0x64 blendThreshold (float)

    // Placeholder members (we don't know full layout)
    char gap0[0x10];
    float currentQuat[4];   // +0x10
    char gap20[0x30 - 0x1c]; // adjust
    char field_0x30;        // +0x30
    int field_0x34;         // +0x34
    char field_0x38;        // +0x38
    char isBlending;        // +0x3a
    char previousEnable;    // +0x3b
    char gap3c[0x64 - 0x3c];
    float blendThreshold;   // +0x64
};

// Globals (from data references)
extern float g_timeOffset;          // DAT_00e44564
extern float g_blendAdd;            // DAT_00d5eeec
extern float g_blendScale;          // DAT_00e50e5c
extern float g_blendThresholdScale; // DAT_00e445c8
extern float g_defaultThreshold;    // DAT_00d5eea0

// External functions (declared)
float __thiscall getEngineTime(void);            // 0x00471610
void __cdecl someWait(void);                     // 0x00b9a9fa
float __cdecl mathAbs(float);                    // 0x004a1580
bool __thiscall isGamePaused(void);              // 0x00410eb0
void __thiscall applyBlend(const float* quat);  // 0x006daa50
void __thiscall resetBlend(const float* src);   // 0x006c0810

// The function
int __thiscall CameraBlend::update(char param2, char param3, float param4) {
    bool bVar2 = (param2 != 0) || (param3 != 0);
    int engineTimePtr = getEngineTime(); // returns pointer to time struct?
    float timeX = *(float*)(engineTimePtr + 0x20); // first component of time vector
    float timeY = *(float*)(engineTimePtr + 0x28);
    double delta = (double)(g_timeOffset - timeX);
    someWait();
    float fVar6 = (float)delta;
    if (this->isBlending != 0) {
        fVar6 = mathAbs(fVar6 + g_blendAdd);
    }

    // Read current quat from this
    float local_20[4];
    local_20[0] = this->currentQuat[0];
    local_20[1] = this->currentQuat[1];
    local_20[2] = this->currentQuat[2];
    local_20[3] = this->currentQuat[3];

    float absDiff = mathAbs(local_20[0] - fVar6);
    bool bVar1 = false;
    char pauseState = isGamePaused(); // 0 = not paused
    if (pauseState == 0 && param4 != 0.0f) {
        bVar1 = true;
    }

    if (bVar2) {
        if (this->isBlending != 0) goto LAB_006c1dc3;
        this->isBlending = 1;
        if (param2 != 0) {
            if (this->blendThreshold == g_defaultThreshold &&
                absDiff < g_blendScale * g_blendThresholdScale) {
                // Compute new target
                float newX = mathAbs(fVar6 + g_blendAdd);
                local_20[0] = newX;
                local_20[1] = 0.0f;
                local_20[2] = 0.0f;
                local_20[3] = 0.0f;
                applyBlend(local_20);
                goto LAB_006c1d87;
            }
        }
    } else {
        if (this->isBlending == 0) goto LAB_006c1dc3;
        this->isBlending = 0;
        if (this->previousEnable != 0) {
            if (this->blendThreshold == g_defaultThreshold &&
                absDiff < g_blendScale * g_blendThresholdScale &&
                !bVar1) {
                float newX = mathAbs(fVar6 + g_blendAdd);
                local_20[0] = newX;
                local_20[1] = 0.0f;
                local_20[2] = 0.0f;
                local_20[3] = 0.0f;
                applyBlend(local_20);
                goto LAB_006c1d87;
            }
        }
    }
    this->blendThreshold = 0.0f;

LAB_006c1dc3:
    this->previousEnable = param2;
    return 0;

LAB_006c1d87:
    this->currentQuat[0] = local_20[0];
    this->currentQuat[1] = local_20[1];
    this->currentQuat[2] = local_20[2];
    this->currentQuat[3] = local_20[3];
    resetBlend((const float*)&engineTimePtr); // parameter likely time vector
    this->previousEnable = param2;
    this->field_0x38 = 1;
    this->field_0x34 = 0;
    this->field_0x30 = 1;
    return 1;
}