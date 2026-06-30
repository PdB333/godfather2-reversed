// FUNC_NAME: InputManager::processControllerAnalogInput
#include <cstdint>

// fwd decls
void FUN_00417cf0(int a, int b, int c); // setInputProfile / applyDeadZone
void FUN_005392b0();
void FUN_0053a3d0();
void FUN_0053a320();
void FUN_0053a370();
void FUN_005388a0();
void* FUN_0060cd00(int param1, int param2, int param3, int param4, int param5); // allocate/initialize
void FUN_0060cde0(); // free or commit
void FUN_00539250();
void FUN_00609340(int type, uint32_t oldVal1, uint32_t oldVal2); // update input event / profile
void FUN_00606e60(uint32_t handle, uint32_t flags);
void FUN_006189c0();

// Global state (addresses from Ghidra export)
// Input state block at 0x012066f0 (11 ints + 1 float?)
static int32_t& s_currentAnalog0 = *(int32_t*)0x012066f0;   // +0x00
static int32_t& s_currentAnalog1 = *(int32_t*)0x012066f4;   // +0x04
static int32_t& s_currentAnalog2 = *(int32_t*)0x012066f8;   // +0x08
static int32_t& s_currentAnalog3 = *(int32_t*)0x012066fc;   // +0x0C
static int32_t& s_currentAnalog4 = *(int32_t*)0x01206700;   // +0x10
static int32_t& s_currentAnalog5 = *(int32_t*)0x01206704;   // +0x14
static int32_t& s_currentAnalog6 = *(int32_t*)0x01206708;   // +0x18
static int32_t& s_currentAnalog7 = *(int32_t*)0x0120670c;   // +0x1C
static int32_t& s_currentAnalog8 = *(int32_t*)0x01206710;   // +0x20
static int32_t& s_currentAnalog9 = *(int32_t*)0x01206714;   // +0x24
static int32_t& s_currentAnalog10 = *(int32_t*)0x01206718;  // +0x28
static int32_t& s_currentAnalog11 = *(int32_t*)0x0120671c;  // +0x2C
static float& s_analogAccumulator = *(float*)0x01206720;    // +0x30

// Previous state block at 0x01206730 (12 ints)
static int32_t& s_previousAnalog0 = *(int32_t*)0x01206730;  // +0x00
static int32_t& s_previousAnalog1 = *(int32_t*)0x01206734;  // +0x04
static int32_t& s_previousAnalog2 = *(int32_t*)0x01206738;  // +0x08
static int32_t& s_previousAnalog3 = *(int32_t*)0x0120673c;  // +0x0C
static int32_t& s_previousAnalog4 = *(int32_t*)0x01206740;  // +0x10
static int32_t& s_previousAnalog5 = *(int32_t*)0x01206744;  // +0x14
static int32_t& s_previousAnalog6 = *(int32_t*)0x01206748;  // +0x18
static int32_t& s_previousAnalog7 = *(int32_t*)0x0120674c;  // +0x1C
static int32_t& s_previousAnalog8 = *(int32_t*)0x01206750;  // +0x20
static int32_t& s_previousAnalog9 = *(int32_t*)0x01206754;  // +0x24
static int32_t& s_previousAnalog10 = *(int32_t*)0x01206758; // +0x28
static int32_t& s_previousAnalog11 = *(int32_t*)0x0120675c; // +0x2C

// Other globals
static int32_t& s_lastKnownAnalog0 = *(int32_t*)0x011f3910; // used for comparison
static int32_t& s_lastKnownAnalog1 = *(int32_t*)0x011f3914; // used for comparison
static float& s_thresholdDeadZone = *(float*)0x00e2af44;   // deadzone min
static float& s_thresholdSensitivity = *(float*)0x00e2b1a4; // sensitivity max?
static float& s_motionSensitivity = *(float*)0x00e2e780;   // threshold for change detection
static uint32_t& s_signMask = *(uint32_t*)0x00e44680;      // e.g. 0x7FFFFFFF (abs mask)

static int32_t& s_globalFlag = *(int32_t*)0x011f3910;      // reused as flag
static int32_t& s_globalFlag2 = *(int32_t*)0x011f3914;

// Input handler object vtable at 0x01205750
static void* s_inputHandlerObject = *(void**)0x01205750;
// vtable offset 0x9c = 39th function (roughly)
typedef void (*InputTriggerFunc)(void* obj, int arg);
static InputTriggerFunc s_inputTrigger = (InputTriggerFunc)(*(void***)s_inputHandlerObject)[0x9c / 4];

// Calibration / profile related
static int32_t& s_calibrationValue = *(int32_t*)0x012058d0; // min clamp
static int32_t& s_calibrationMax = *(int32_t*)0x00f15988;   // max clamp? Symmetric?
static int32_t& s_profileFlag1 = *(int32_t*)0x011f3a30;
static int32_t& s_profileFlag2 = *(int32_t*)0x011f39f4;
static int32_t& s_profileFlag3 = *(int32_t*)0x011f3a3c;
static int32_t& s_profileFlag4 = *(int32_t*)0x011f3a38;
static int32_t& s_profileFlag5 = *(int32_t*)0x011f3a14;
static int32_t& s_profileFlag6 = *(int32_t*)0x011f3a44;

// Player / controller ID
static uint32_t& s_playerControllerId = *(uint32_t*)0x012058a8;
static uint32_t& s_playerEntityPtr = *(uint32_t*)0x012054dc;
// Array of player state? base address 0x011a0f28 with size 0x38 per entry

void FUN_0052d610() // process analog input changes / calibration
{
    int32_t savedFlag2 = s_globalFlag2;
    
    // Check if input state is zero or invalid
    if (s_analogAccumulator == 0.0f || s_currentAnalog0 == 0 ||
        (s_currentAnalog7 < s_thresholdDeadZone && s_currentAnalog10 < s_thresholdDeadZone))
    {
        // Not enough input -> clear previous state
        s_previousAnalog0 = 0;
    }
    else
    {
        // If accumulator is below sensitivity threshold, scale inputs
        if (s_analogAccumulator < s_thresholdSensitivity)
        {
            s_currentAnalog7 *= s_analogAccumulator;
            s_currentAnalog10 *= s_analogAccumulator;
        }
        
        // Check if any axis changed by more than motionSensitivity (using absolute difference)
        if (s_currentAnalog0 != s_previousAnalog0 || // didn't actually compare? Actually the condition is complex
            // The original: if any of these differences exceed threshold, update snapshot
            ((uint32_t)(s_currentAnalog8 - s_previousAnalog8) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog9 - s_previousAnalog9) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog10 - s_previousAnalog10) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog11 - s_previousAnalog11) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog4 - s_previousAnalog4) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog5 - s_previousAnalog5) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog6 - s_previousAnalog6) & s_signMask) > s_motionSensitivity ||
            ((uint32_t)(s_currentAnalog7 - s_previousAnalog7) & s_signMask) > s_motionSensitivity)
        {
            // Copy current to previous snapshot
            s_previousAnalog0 = s_currentAnalog0;
            s_previousAnalog1 = s_currentAnalog1;
            s_previousAnalog2 = s_currentAnalog2;
            s_previousAnalog3 = s_currentAnalog3;
            s_previousAnalog4 = s_currentAnalog4;
            s_previousAnalog5 = s_currentAnalog5;
            s_previousAnalog6 = s_currentAnalog6;
            s_previousAnalog7 = s_currentAnalog7;
            s_previousAnalog8 = s_currentAnalog8;
            s_previousAnalog9 = s_currentAnalog9;
            s_previousAnalog10 = s_currentAnalog10;
            s_previousAnalog11 = s_currentAnalog11;
        }
    }
    
    // Reset accumulator
    s_analogAccumulator = 0.0f;
    
    // If previous state is non-zero and one of the axes exceeds deadzone
    if (s_previousAnalog0 != 0 && (s_thresholdDeadZone <= s_previousAnalog7 || s_thresholdDeadZone <= s_previousAnalog10))
    {
        bool lastFlag = (s_lastKnownAnalog0 != 0);
        s_lastKnownAnalog0 = 0;
        s_globalFlag2 = 0;
        if (lastFlag || savedFlag2 != 0)
        {
            s_inputTrigger(s_inputHandlerObject, 0);
        }
        
        // Apply calibration / clamping to several config values
        // This section sets up deadzone profiles
        if (s_calibrationValue < 22) s_calibrationValue = 22;
        if (s_calibrationMax > 22) s_calibrationMax = 22;
        s_profileFlag1 = 1;
        if (s_calibrationValue < 7) s_calibrationValue = 7;
        if (s_calibrationMax > 7) s_calibrationMax = 7;
        s_profileFlag2 = 0;
        if (s_calibrationValue < 25) s_calibrationValue = 25;
        if (s_calibrationMax > 25) s_calibrationMax = 25;
        s_profileFlag3 = 5;
        if (s_calibrationValue < 24) s_calibrationValue = 24;
        if (s_calibrationMax > 24) s_calibrationMax = 24;
        s_profileFlag4 = 0;
        if (s_calibrationValue < 15) s_calibrationValue = 15;
        if (s_calibrationMax > 15) s_calibrationMax = 15;
        s_profileFlag5 = 0;
        if (s_calibrationValue < 27) s_calibrationValue = 27;
        if (s_calibrationMax > 26) s_calibrationMax = 27;
        s_profileFlag6 = 1;
        
        FUN_00417cf0(1, 5, 6); // Apply profile settings
        FUN_005392b0(); // Reset/calibrate controller
        
        // Update player state if needed
        uint32_t controllerId = s_playerControllerId;
        if (s_playerEntityPtr != 0)
        {
            controllerId = *(uint32_t*)(s_playerEntityPtr + 0x170);
        }
        if (controllerId != 0xFFFFFFFF && controllerId < 0x1000)
        {
            int offset = controllerId * 0x38;
            byte* playerStateArray = (byte*)0x011a0f28;
            if (playerStateArray[offset] < 4)
            {
                int* flagsPtr = (int*)(0x011a0f44 + offset);
                if (*flagsPtr != 0)
                {
                    FUN_00606e60(*flagsPtr, 0x210000);
                }
                *(uint32_t*)(0x011a0f34 + offset) = (*(uint32_t*)(0x011a0f34 + offset) & 0xFCAD8FFF) | 0x210000;
                FUN_006189c0();
            }
        }
        
        FUN_0053a3d0();
        FUN_0053a320();
        FUN_0053a370();
        FUN_005388a0();
        
        void* block = FUN_0060cd00(5, 4, 0, 1, 0);
        if (block != 0)
        {
            float val = *(float*)0x00e2eff4;
            float sens = *(float*)0x00e2b1a4;
            ((float*)block)[0] = *(float*)0x00e2eff4;
            ((float*)block)[1] = val;
            ((float*)block)[2] = sens;
            ((float*)block)[3] = val;
            ((float*)block)[4] = val;
            ((float*)block)[5] = sens;
            ((float*)block)[6] = sens;
            ((float*)block)[7] = sens;
            FUN_0060cde0();
        }
        
        FUN_00539250();
        
        // Second pass of calibration (with different target values)
        if (s_calibrationValue < 22) s_calibrationValue = 22;
        if (s_calibrationMax > 22) s_calibrationMax = 22;
        s_profileFlag1 = 1;
        if (s_calibrationValue < 7) s_calibrationValue = 7;
        if (s_calibrationMax > 7) s_calibrationMax = 7;
        s_profileFlag2 = 1;
        if (s_calibrationValue < 25) s_calibrationValue = 25;
        if (s_calibrationMax > 25) s_calibrationMax = 25;
        s_profileFlag3 = 7;
        if (s_calibrationValue < 24) s_calibrationValue = 24;
        if (s_calibrationMax > 24) s_calibrationMax = 24;
        s_profileFlag4 = 0;
        if (s_calibrationValue < 15) s_calibrationValue = 15;
        if (s_calibrationMax > 15) s_calibrationMax = 15;
        s_profileFlag5 = 0;
        if (s_calibrationValue < 27) s_calibrationValue = 27;
        if (s_calibrationMax > 26) s_calibrationMax = 27;
        s_profileFlag6 = 0;
        
        FUN_00417cf0(1, 5, 6);
        
        uint32_t oldVal1 = s_globalFlag2;
        uint32_t oldVal2 = s_globalFlag1;
        s_globalFlag1 = s_playerControllerId;
        if (s_playerEntityPtr != 0)
        {
            s_globalFlag1 = *(uint32_t*)(s_playerEntityPtr + 0x170);
        }
        s_globalFlag2 = 0;
        
        FUN_00609340(4, oldVal2, oldVal1);
    }
}