// FUNC_NAME: InputDeviceManager::selectActiveControllerFromAnalogInputs

// Function address: 0x007fbed0
// This function iterates over 8 controller input slots (likely analog triggers or sticks),
// finds the one with the highest magnitude value (from FUN_008c95c0), and if that value
// exceeds a global threshold (DAT_00d577a0), it activates/registers that controller
// by calling FUN_008c93f0 and stores the slot index and a constant force feedback value.

#include <cstdint>

// External functions (callees) - assumed to be in same module
extern float __fastcall getControllerInputMagnitude(int slotIndex); // FUN_008c95c0
extern void __fastcall activateControllerInput(void* pThis, int slotIndex); // FUN_008c93f0
extern float __fastcall getControllerOtherValue(); // FUN_008c9590 - possibly force feedback strength

// Global variables referenced
extern float g_initialMaxValue;   // DAT_00d5ccf8 - initial maximum for comparison
extern float g_inputThreshold;    // DAT_00d577a0 - minimum value to activate
extern float g_constantFeedback;  // DAT_00e544c8 - constant value written to field

void __fastcall InputDeviceManager::selectActiveControllerFromAnalogInputs(void* param_1)
{
    uint selectedIdx = 0;
    float maxValue = g_initialMaxValue;  // start with global default
    
    uint slotIdx = 0;
    do {
        float currentValue = getControllerInputMagnitude(slotIdx);
        if (maxValue < currentValue) {
            selectedIdx = slotIdx;
            maxValue = currentValue;
        }
        slotIdx++;
    } while (slotIdx < 8);  // iterate over 8 controller slots
    
    if (g_inputThreshold <= maxValue) {
        // This slot exceeds the activation threshold
        activateControllerInput(param_1, selectedIdx);
        
        // Retrieve some other value from the activated controller (e.g., trigger/rumble)
        float otherValue = getControllerOtherValue();
        // Store the other value at offset +0x79c (but immediately overwritten below)
        *(float*)((char*)param_1 + 0x79c) = otherValue;
        
        // Store the selected slot index at offset +0x7a0
        *(uint*)((char*)param_1 + 0x7a0) = selectedIdx;
        
        // Overwrite the value at +0x79c with a constant (likely force feedback or threshold)
        *(float*)((char*)param_1 + 0x79c) = g_constantFeedback;
        // Note: the previous write to +0x79c is useless due to this overwrite;
        // this may indicate a union or miscompilation.
    }
    return;
}