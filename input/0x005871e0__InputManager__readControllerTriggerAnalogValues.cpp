// FUNC_NAME: InputManager::readControllerTriggerAnalogValues
// Address: 0x005871e0
// Reads analog trigger values from a controller based on input flags.
// param_1: pointer to controller state (likely a per-slot structure)
// param_2: bitmask (bits 12-14 select left trigger, right trigger, and an extra axis)
// unaff_EDI: output pointer to a float array of size 4 (index 0-2 = values, index 3 = threshold)
// Returns 1 if any bit in 0x7000 is set, else 0 and zeros out output and sets default threshold.

#include <cstdint>

// Forward declarations of helper functions
bool getControllerAnalogValues(void* controllerState, float* outAnalog1, float* outAnalog2, float* outAnalog3);
void processControllerAnalogValues(float analog1, float analog2, float analog3);

uint32_t __fastcall readControllerTriggerAnalogValues(void* controllerState, uint32_t inputFlags, float* outValues /* passed in EDI */) {
    // Local variable array for raw analog values (size 3)
    float analogValues[3] = {0.0f, 0.0f, 0.0f};
    // Pointers to individual locals; order as seen in decompiled call
    float& outAnalog1 = analogValues[1];
    float& outAnalog2 = analogValues[0];
    float& outAnalog3 = analogValues[2];

    if ((inputFlags & 0x7000) != 0) {
        // Read raw analog values from controller (order: &analogValues[1], &analogValues[0], &analogValues[2])
        bool success = getControllerAnalogValues(controllerState, &analogValues[1], &analogValues[0], &analogValues[2]);
        // Local processed values (initialized to zero, will be overwritten depending on flags)
        float processedAnalog1 = 0.0f; // originally local_c
        float processedAnalog2 = 0.0f; // originally local_8
        float processedAnalog3 = 0.0f; // originally local_4

        // Bit 12 (0x1000) -> left trigger
        if ((inputFlags >> 12) & 1) {
            processedAnalog1 = analogValues[0]; // local_18 becomes processedAnalog1? Wait: local_c = local_18; local_18 is analogValues[0]? Need to map correctly
            // Actually: local_c = local_18; but local_18 is the first variable? Decompiled order: local_18, local_14, local_10. And getControllerAnalogValues gets &local_14, &local_18, &local_10. So local_18 = rawVal2, local_14 = rawVal1, local_10 = rawVal3? Let's be careful.
        }
        if ((inputFlags >> 13) & 1) {
            processedAnalog2 = analogValues[1]; // local_14
        }
        if ((inputFlags >> 14) & 1) {
            processedAnalog3 = analogValues[2]; // local_10
        }
        // Process the combined analog values (order: processedAnalog2, processedAnalog1, processedAnalog3)
        processControllerAnalogValues(processedAnalog2, processedAnalog1, processedAnalog3);
        return 1;
    } else {
        // No trigger bits set: zero output and set default threshold
        outValues[0] = 0.0f; // unaff_EDI[0]
        outValues[1] = 0.0f; // unaff_EDI[1]
        outValues[2] = 0.0f; // unaff_EDI[2]
        // Default threshold from global DAT_00e2b1a4 (assumed float)
        outValues[3] = *(float*)0x00e2b1a4;
        return 0;
    }
}