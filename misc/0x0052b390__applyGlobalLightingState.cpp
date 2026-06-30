// FUNC_NAME: applyGlobalLightingState
void applyGlobalLightingState(float timeFactor)
{
    int state;
    uint previousLocation;
    int brightnessClamp;
    
    previousLocation = s_currentLocationId;
    if ((s_currentLocationId != s_previousLocationId) || (s_transitionFlag != 0)) {
        FUN_00609890(1);
    } else {
        FUN_0060df60(s_currentLocationId, s_previousLocationId);
    }
    
    // Clamp brightness values
    brightnessClamp = 0x16; // 22
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp; // min
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp; // max?
    
    s_globalFlag1 = 1; // +0x3a30
    brightnessClamp = 0xe; // 14
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag2 = 0; // +0x3a10
    
    brightnessClamp = 0x19; // 25
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag3 = 5; // +0x3a3c
    
    brightnessClamp = 0x18; // 24
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag4 = 0; // +0x3a38
    
    brightnessClamp = 0xf; // 15
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag5 = 0; // +0x3a14
    
    state = s_currentMode; // in_EAX as a global mode (0,1,2)
    if (state == 0) {
        FUN_00417cf0(1, 2, 2); // set lighting preset
    } else {
        if (state == 1) {
            timeFactor = (float)((int)(timeFactor * s_brightnessScale) & 0xff);
            FUN_00417f00(timeFactor, timeFactor, timeFactor, timeFactor); // set uniform color
            FUN_00417cf0(1, 0xe, 0xf); // set different preset
        } else {
            if (state == 2) {
                FUN_00417cf0(3, 2, 2);
            } else {
                FUN_00417cf0(1, 2, 2);
            }
        }
    }
    
    s_someColor1 = s_colorA;
    s_someColor2 = s_colorB;
    s_flashFlag = 4; // +0x19a6c
    if (s_currentLightPtr == &s_lightData) {
        FUN_0060a460(s_colorA);
        FUN_0060a460(s_colorB);
    }
    FUN_00530a60(); // update shadows?
    
    if ((previousLocation != 0xffffffff) && (previousLocation < 0x1000)) {
        int index = previousLocation * 0x38;
        if ((&s_locationData + index != (byte *)0x0) && ((byte)(&s_locationData)[index] < 4)) {
            if (*(int *)(&s_locationData + 0x1c + index) != 0) {
                FUN_00606e60(*(int *)(&s_locationData + 0x1c + index), 0x100000);
            }
            *(uint *)(&s_locationData + 0xc + index) = *(uint *)(&s_locationData + 0xc + index) & 0xfc9c8fff | 0x100000;
            FUN_006189c0();
        }
    }
    
    FUN_00530df0(); // update something else
    brightnessClamp = 0x1b; // 27
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag6 = 0; // +0x3a44
    
    FUN_0052ae50(); // some setup
    FUN_00612e00(); // reset timer?
    
    s_someColor2 = 0;
    s_someColor1 = 0;
    s_otherFlag1 = 0;
    s_otherFlag2 = 0;
    
    // Repeat initial clamping sequence
    brightnessClamp = 0x16;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag1 = 1;
    
    brightnessClamp = 0x19;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag3 = 7;
    
    brightnessClamp = 0x18;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag4 = 0;
    
    brightnessClamp = 0xf;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag5 = 0;
    
    brightnessClamp = 0x1b;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    s_globalFlag6 = 0;
    
    FUN_00417cf0(1, 5, 6);
    
    brightnessClamp = 0xe;
    if (s_lightBrightness < brightnessClamp) s_lightBrightness = brightnessClamp;
    s_globalFlag2 = 1;
    if (s_lightMax > brightnessClamp) s_lightMax = brightnessClamp;
    
    return;
}