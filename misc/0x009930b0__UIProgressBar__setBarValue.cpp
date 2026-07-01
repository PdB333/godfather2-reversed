// FUNC_NAME: UIProgressBar::setBarValue

#include <math.h>

// Globals (inferred from DAT addresses)
extern char* g_config;          // DAT_01129938
extern char* g_defaults;        // DAT_0122348c
extern float g_barMin;          // DAT_00d92140
extern float g_barRange;        // DAT_00e576b8
extern float g_barMaxClamp;     // DAT_00d5780c
extern float g_barScale;        // DAT_00d5d7b8
extern float g_barOffset;       // DAT_00d5c458
extern const char* g_barName;   // DAT_00d921ec

// Helper function declarations
extern void FUN_0090cec0(float value); // Likely a clamp/normalization function
extern void FUN_005a04a0(const char* action, int param2, const char* name, int param4); // Logging

void __thiscall UIProgressBar::setBarValue(int this)
{
    float fVar1;
    float normalizedValue;
    int pixelValue;

    // Select source value based on state flag at global config+0x30
    if (*(char*)(g_config + 0x30) == '\0') {
        fVar1 = *(float*)(g_defaults + 0x60); // Default bar value
    } else {
        fVar1 = *(float*)(g_config + 0x2c);   // Config bar value
    }

    // Apply some transformation (e.g., clamping)
    FUN_0090cec0(fVar1);

    // Normalize: (value - min) / range
    normalizedValue = (fVar1 - g_barMin) / g_barRange;

    // Clamp normalized value to [0.0, g_barMaxClamp]
    if (normalizedValue < 0.0f) {
        normalizedValue = 0.0f;
    } else if (g_barMaxClamp < normalizedValue) {
        normalizedValue = g_barMaxClamp;
    }

    // Convert to pixel coordinate: round(normalized * scale + offset)
    pixelValue = (int)round(normalizedValue * g_barScale + g_barOffset);

    // Store result to two locations (likely start and end, or x and y of bar)
    *(int*)(this + 0x50) = pixelValue; // +0x50: bar start offset?
    *(int*)(this + 0x54) = pixelValue; // +0x54: bar end offset?

    // Log the set operation
    FUN_005a04a0("SetBar", 0, g_barName, 0);
}