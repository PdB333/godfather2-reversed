// FUN_0041ddf0: InputManager::areAnalogInputsNeutral
// Checks if all analog input axes are neutral (0.0) and if a threshold condition is met.
// Returns true if all axes are zero AND current value <= threshold, else returns whether a flag is zero.
// Global variables at 0x01206ab4..0x01206ae8 are likely analog stick/trigger values (float).
// DAT_01206aa0 is probably a current axis value (float).
// PTR_FUN_00e4462c is likely a float threshold variable (mislabeled by Ghidra as pointer).
// DAT_01206a80 is a byte flag controlling alternative return.

bool InputManager::areAnalogInputsNeutral()
{
    bool bAllZero;

    // Check if all 12 analog inputs are exactly zero
    if (gAnalogInput0 == 0.0f &&                      // +0x01206ab4
        gAnalogInput1 == 0.0f &&                      // +0x01206ab8
        gAnalogInput2 == 0.0f &&                      // +0x01206abc
        gAnalogInput3 == 0.0f &&                      // +0x01206ac0
        gAnalogInput4 == 0.0f &&                      // +0x01206ac8
        gAnalogInput5 == 0.0f &&                      // +0x01206acc
        gAnalogInput6 == 0.0f &&                      // +0x01206ad0
        gAnalogInput7 == 0.0f &&                      // +0x01206ad4
        gAnalogInput8 == 0.0f &&                      // +0x01206adc
        gAnalogInput9 == 0.0f &&                      // +0x01206ae0
        gAnalogInput10 == 0.0f &&                     // +0x01206ae4
        gAnalogInput11 == 0.0f)                       // +0x01206ae8
    {
        bAllZero = true;
    }
    else
    {
        bAllZero = false;
    }

    // If current value is below threshold and all analog inputs are zero, return true
    if (gCurrentAnalogValue <= gAnalogThreshold && bAllZero)
    {
        return true;
    }

    // Otherwise return whether an enable byte is zero
    return gEnableFlag == '\0';
}

// External globals (actual addresses in the binary)
extern float gAnalogInput0;      // 0x01206ab4
extern float gAnalogInput1;      // 0x01206ab8
extern float gAnalogInput2;      // 0x01206abc
extern float gAnalogInput3;      // 0x01206ac0
extern float gAnalogInput4;      // 0x01206ac8
extern float gAnalogInput5;      // 0x01206acc
extern float gAnalogInput6;      // 0x01206ad0
extern float gAnalogInput7;      // 0x01206ad4
extern float gAnalogInput8;      // 0x01206adc
extern float gAnalogInput9;      // 0x01206ae0
extern float gAnalogInput10;     // 0x01206ae4
extern float gAnalogInput11;     // 0x01206ae8
extern float gCurrentAnalogValue; // 0x01206aa0
extern float gAnalogThreshold;   // 0x00e4462c (originally misidentified as pointer)
extern char gEnableFlag;         // 0x01206a80