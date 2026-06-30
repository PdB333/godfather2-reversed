// FUNC_NAME: WeatherManager::applyWeatherState

// Address: 0x0051fc90
// This function applies a weather/state configuration based on flags in the weather state object.
// It updates global environment settings (fog, lighting, color corrections) and iterates over
// lists of associated objects to apply the state.
// Parameters:
//   instant - if true, apply instantly; if false, consider transition flags.

#include <cstdint>

// Forward declarations for called functions (not defined here)
void WeatherManager_setTimeOfDay(uint timeOfDay);     // 0x0053b1e0
void RENDER_setGlobalParam(uint param, float val);    // 0x0060a460 (generic)
void WeatherManager_updateGlobals();                   // 0x0053b320
void RENDER_setFog(int a, int b, int c);               // 0x00417cf0
void RENDER_setAmbientColor(float r, float g, float b); // 0x0041e660
void ObjectManager_setFlags(void* obj, uint flags);   // 0x00606e60
void ObjectManager_assignData(void* dest, void* src, void* data); // 0x0060add0
void WeatherManager_applyForcedState(void* state);    // 0x0053b3e0
void WeatherManager_processPendingQueue(void* param); // 0x0053bb60
void WeatherManager_handleRain();                      // 0x0053b4f0
void RENDER_applyFogColor(float* color);               // 0x00417f00? not sure
void RENDER_setFogRange(int a, int b, int c, int d);  // 0x00417db0
void RENDER_setColorCorrection(float* color);          // 0x00417f00 (maybe)
void LightManager_applyState(bool enable);             // 0x004ec7a0
void WeatherManager_updateLighting();                  // 0x0053ba20
void WeatherManager_updateShadowMap(int param);        // 0x0053bab0
void WeatherManager_clearState(void* state);           // 0x0053b420
void DebugRenderer_flush();                            // 0x00618d40

// Global variables (addresses from Ghidra)
extern uint32_t DAT_01125380;
extern uint32_t DAT_01125384;
extern uint32_t DAT_01125388; // index into some table (+0x11253f0, stride 0x38)
extern uint32_t DAT_0112537c;
extern uint8_t DAT_01125389;   // index into another table (+0x11254bc, stride 0x3c)
extern uint32_t DAT_011252e8;
extern uint32_t DAT_011252ec;
extern uint32_t DAT_012058e8;
extern uint32_t DAT_012058f0;
extern uint32_t DAT_012058d0;   // min quality/setting
extern uint32_t DAT_00f15988;   // max quality/setting
extern uint32_t _DAT_011f3a30;  // lighting flags
extern uint32_t _DAT_011f39f4;
extern uint32_t _DAT_011f3a10;
extern uint32_t _DAT_011f3a3c;
extern uint32_t _DAT_011f3a38;
extern uint32_t _DAT_011f3a14;
extern uint32_t _DAT_011f3a44;
extern uint32_t _DAT_01125378;
extern uint32_t _DAT_01125394;
extern uint32_t _DAT_011253e4;
extern uint32_t _DAT_011253e8;
extern uint32_t _DAT_011253ec;
extern uint32_t DAT_012058f4;
extern float DAT_00e2b1a4;     // extra color component (alpha?)
extern uint32_t* PTR_PTR_011252d8; // pointer array
extern uint8_t DAT_012054eb;
extern uint8_t DAT_012054fc;
extern uint32_t DAT_011f6680;
extern uint8_t DAT_011eb8fc[]; // array indexed by DAT_011252ec * 0x10
extern uint8_t DAT_011d912c[]; // array indexed by uVar7

void FUN_0051fc90(uint32_t param_1) {
    // this pointer is in EAX: points to a handle that itself points to the weather state object
    uint32_t handle = *((uint32_t*)this);
    if (handle == 0) {
        return;
    }

    uint16_t flags = *(uint16_t*)(handle + 0x44); // +0x44: weather state flags
    uint32_t isNightOrForce; // local_28, becomes 0 or 1
    isNightOrForce = 1;

    if ((int8_t)param_1 == 0) { // not instant
        if ((flags & 0x400) != 0) {
            return; // some flag prevents processing
        }
        if ((flags & 0x200) != 0) {
            isNightOrForce = 0;
        }
    } else { // instant
        if ((flags & 0x200) == 0) {
            return;
        }
        // if 0x200 set, continue
    }

    if ((int8_t)param_1 == 0) {
        // Non-instant: determine time of day from flags
        uint32_t timeOfDay = 0;
        if ((int16_t)flags < 0) { // check sign bit? (0x8000)
            timeOfDay = 2;
        } else if ((flags & 0x20) != 0) {
            timeOfDay = 1;
        }
        WeatherManager_setTimeOfDay(timeOfDay); // 0x0053b1e0
    } else {
        // Instant: set global constants for forced weather
        DAT_01125380 = 0;
        DAT_01125384 = 0;
        DAT_01125388 = 2;
        if (*(uint32_t*)(handle + 12) == 0) { // in_EAX[3] - some pointer
            DAT_0112537c = 4;
            DAT_01125389 = 0x13;
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253e4;
        } else if ((flags & 0x4000) == 0) {
            DAT_0112537c = 5;
            DAT_01125389 = 0x14;
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253e8;
        } else {
            DAT_0112537c = 6;
            DAT_01125389 = 0x15;
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253ec;
        }
    }

    // Set global pointer array and apply some global parameters
    DAT_012058e8 = (uint32_t*)&PTR_PTR_011252d8;
    RENDER_setGlobalParam(DAT_011252e8, 0.0f); // 0x0060a460 (float version)
    RENDER_setGlobalParam(DAT_011252ec, 0.0f); // 0x0060a460
    WeatherManager_updateGlobals(); // 0x0053b320

    // Set lighting flags based on another flag (0x1000)
    if ((*(uint16_t*)(handle + 0x44) & 0x1000) == 0) {
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 3;
    } else {
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
    }

    // Apply fog settings
    RENDER_setFog(1, 5, 6); // 0x00417cf0
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = 1;

    // Ambient color setup
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 1;
    RENDER_setAmbientColor(*(float*)&_DAT_00e2d7d4, *(float*)&_DAT_00e2d7d8); // 0x0041e660

    // More quality thresholds (shadow? bloom?)
    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 5;
    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;
    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;

    // Set object flags for some associated objects
    if (*(uint32_t*)(handle + 12) != 0) { // in_EAX[3]
        ObjectManager_setFlags((void*)*(uint32_t*)(handle + 12), 0x300000); // 0x00606e60
    }
    if (*(uint32_t*)(handle + 16) != 0) { // in_EAX[4]
        ObjectManager_setFlags((void*)*(uint32_t*)(handle + 16), 0x3034000); // 0x00606e60
    }

    // Assign some data from a table
    int index = (uint8_t)DAT_01125389 * 0x3c + 0x11254bc;
    int* entry = *(int**)index;
    if (entry != 0) {
        ObjectManager_assignData((void*)DAT_011252ec, entry, &DAT_011f6680); // 0x0060add0
    }

    if ((int8_t)param_1 != 0) {
        WeatherManager_applyForcedState((void*)*(uint32_t*)(handle + 16)); // 0x0053b3e0
    }

    WeatherManager_processPendingQueue((void*)DAT_012058f4); // 0x0053bb60

    // Handle rain if flag set
    if ((*(uint8_t*)(handle + 0x44) & 0x80) != 0) {
        WeatherManager_handleRain(); // 0x0053b4f0
    }

    // Prepare color vector from object
    int base = *(int*)handle; // *in_EAX
    float colorR = *(float*)(base + 0x78);
    float colorG = *(float*)(base + 0x7c);
    float colorB = *(float*)(base + 0x80);
    float colorA = DAT_00e2b1a4; // global alpha
    // local_20 = colorR, local_1c = colorG, local_18 = colorB, local_14 = colorA

    // Assign color from another table based on DAT_01125388
    int index2 = (uint32_t)DAT_01125388 * 0x38 + 0x11253f0;
    int* entry2 = *(int**)index2;
    if (entry2 != 0) {
        ObjectManager_assignData((void*)DAT_011252e8, entry2, &colorR); // 0x0060add0
    }

    // Adjust quality thresholds again
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 0;

    if ((int8_t)param_1 == 0) {
        // Non-instant: apply some state based on a byte at +0x48
        bool isSunny = (*(int8_t*)(handle + 0x48) != 3);
        RENDER_applyFogColor(isSunny ? 1 : 0); // 0x00417fe0 (takes bool)
        LightManager_applyState(true); // 0x004ec7a0
    } else {
        // Instant: apply different color grading
        RENDER_applyFogColor(1); // 0x00417fe0(1)
        if ((*(uint16_t*)(handle + 0x44) & 0x800) == 0) {
            RENDER_setFogRange(5, 6, 1, 0xe, 6); // 0x00417db0
            // local_24 constructed from byte at +0x46 and other data
            uint8_t byte46 = *(uint8_t*)(handle + 0x46);
            // local_24 low byte is something, rest from previous local_24
            // Simplified: assume CONCAT31 uses high bytes from old local_24
            uint32_t local_24 = (local_24 & 0xFF00FFFF) | ((uint32_t)byte46 << 16);
            RENDER_setColorCorrection((float*)&local_24); // 0x00417f00
        } else {
            RENDER_setFogRange(5, 6, 1, 1, 2); // 0x00417db0
        }
    }

    // More quality settings
    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 5;
    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = (uint32_t)*(uint8_t*)(handle + 0x49); // +0x49 byte
    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = (*(uint8_t*)(handle + 0x49) != 0) ? 1 : 0;

    WeatherManager_updateLighting(); // 0x0053ba20
    WeatherManager_updateShadowMap(0); // 0x0053bab0

    // local_24 updated again
    // Shift of in_EAX[0xd] (offset 0x34) and byte from +0x46
    uint8_t byte46 = *(uint8_t*)(handle + 0x46);
    uint32_t local_24 = ((*(uint32_t*)(handle + 0x34) >> 1) & 0xFF) << 24 | (local_24 & 0x00FFFFFF);
    // Actually the decompiler shows CONCAT31 with local_24._1_3_ ~ high byte replaced.

    // Process two sets of child objects if global flags allow
    if (DAT_012054eb == 0) {
        if (*(uint32_t*)(handle + 8) != 0) { // in_EAX[2]
            ObjectManager_setFlags((void*)*(uint32_t*)(handle + 8), 0x3034000);
        }
        WeatherManager_clearState((void*)*(uint32_t*)(handle + 12)); // in_EAX[3] - 0x0053b420
        // Iterate a list: in_EAX[5] to in_EAX[7]
        uint32_t* it = (uint32_t*)*(uint32_t*)(handle + 20); // in_EAX[5]
        uint32_t* end = (uint32_t*)*(uint32_t*)(handle + 28); // in_EAX[7]
        while (it != end) {
            // Call virtual function at offset +0xc in vtable with parameters
            uint32_t vtable = *(uint32_t*)it;
            void (*applyFunc)(uint32_t, uint32_t, uint32_t, float) = (void (*)(uint32_t, uint32_t, uint32_t, float))(*vtable + 0xc);
            applyFunc(isNightOrForce, param_1, local_24, 0x3f800000f); // 0x3f800000 = 1.0f
            it = (uint32_t*)it[0x10]; // +0x40? next element (likely linked list)
        }
    }

    if (DAT_012054fc == 0) {
        if (*(uint32_t*)(handle + 8) != 0) { // in_EAX[2]
            ObjectManager_setFlags((void*)*(uint32_t*)(handle + 8), 0x3334000);
        }
        WeatherManager_clearState((void*)*(uint32_t*)(handle + 12)); // in_EAX[3]
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
        // Second list: in_EAX[8] to in_EAX[10]
        uint32_t* it = (uint32_t*)*(uint32_t*)(handle + 32); // in_EAX[8]
        uint32_t* end = (uint32_t*)*(uint32_t*)(handle + 40); // in_EAX[10]
        while (it != end) {
            uint32_t vtable = *(uint32_t*)it;
            void (*applyFunc)(uint32_t, uint32_t, uint32_t, float) = (void (*)(uint32_t, uint32_t, uint32_t, float))(*vtable + 0xc);
            applyFunc(isNightOrForce, param_1, local_24, 0x3f800000f);
            it = (uint32_t*)it[0x10];
        }
    }

    // Clear flags on objects
    if (*(uint32_t*)(handle + 8) != 0) { // in_EAX[2]
        ObjectManager_setFlags((void*)*(uint32_t*)(handle + 8), 0x3034000);
    }
    if (*(uint32_t*)(handle + 12) != 0) { // in_EAX[3]
        ObjectManager_setFlags((void*)*(uint32_t*)(handle + 12), 0x3034000);
    }

    uint32_t minVal = DAT_012058d0;
    uint32_t maxVal = DAT_00f15988;

    // Additional debug/index handling
    if (_DAT_01125378 != 0) {
        uint32_t idx = _DAT_01125378 & 0xff;
        if (DAT_011eb8fc[DAT_011252ec * 0x10] != 0) {
            idx += 0x10;
        }
        DebugRenderer_flush(); // 0x00618d40
        minVal = DAT_012058d0;
        maxVal = DAT_00f15988;
        DAT_011d912c[idx] = 0;
    }

    DAT_012058e8 = 0;
    DAT_012058f0 = 0;

    // Final quality thresholds adjustments
    if (minVal < 0x1b) { minVal = 0x1b; DAT_012058d0 = 0x1b; }
    if (maxVal > 0x1a) { maxVal = 0x1b; DAT_00f15988 = 0x1b; }
    _DAT_011f3a44 = 0;

    if (minVal < 0x19) { minVal = 0x19; DAT_012058d0 = 0x19; }
    if (maxVal > 0x19) { maxVal = 0x19; DAT_00f15988 = 0x19; }
    _DAT_011f3a3c = 7;

    if (minVal < 0x18) { minVal = 0x18; DAT_012058d0 = 0x18; }
    if (maxVal > 0x18) { maxVal = 0x18; DAT_00f15988 = 0x18; }
    _DAT_011f3a38 = 0;

    if (minVal < 0xf) { minVal = 0xf; DAT_012058d0 = 0xf; }
    if (maxVal > 0xf) { maxVal = 0xf; DAT_00f15988 = 0xf; }
    _DAT_011f3a14 = 0;

    if (minVal < 0xe) { minVal = 0xe; DAT_012058d0 = 0xe; }
    if (maxVal > 0xe) { maxVal = 0xe; DAT_00f15988 = 0xe; }
    _DAT_011f3a10 = 1;

    if (minVal < 7) { minVal = 7; DAT_012058d0 = 7; }
    if (maxVal > 7) { maxVal = 7; DAT_00f15988 = 7; }
    _DAT_011f39f4 = 1;

    if (minVal < 0x16) { DAT_012058d0 = 0x16; }
    if (maxVal > 0x16) { DAT_00f15988 = 0x16; }
    _DAT_011f3a30 = 1;

    RENDER_setFog(1, 5, 6);
    RENDER_setAmbientColor(0.0f, 0.0f); // 0x0041e660(0,0)
}