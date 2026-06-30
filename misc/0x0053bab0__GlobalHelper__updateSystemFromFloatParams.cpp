// FUNC_NAME: GlobalHelper::updateSystemFromFloatParams

// Reconstructed from 0x0053bab0
// This function appears to be a global helper that processes three float parameters,
// possibly related to input or camera systems. It calculates two intermediate values
// and conditionally calls another function with a pointer retrieved from a global table.

#include <cstdint>

// Global data: assume they are defined elsewhere in the translation unit
extern const float g_fConstant;               // +0x00e44564
extern uint32_t g_activeIndex;               // +0x01125388
extern void* g_globalPointer;                // +0x011252e8

// Structure stored at 0x01125418 array, stride 0x38
struct ObjectEntry {
    int32_t firstField;           // +0x00 (checked for non-zero)
    // ... other fields up to 0x38
};

// Forward declaration of the called function (address 0x0060add0)
void processObjectEntry(void* arg1, ObjectEntry* entry, uint8_t output[8]);

// Main function
void updateSystemFromFloatParams(float param_a, float param_b, float param_c)
{
    // Compute intermediate values (unused in decompiled code, but present in original)
    float temp1 = g_fConstant - param_b * param_c;   // local_18
    float temp2 = g_fConstant - param_a * param_c;   // local_14

    // Retrieve object entry from global table using index
    ObjectEntry* entry = reinterpret_cast<ObjectEntry*>(0x01125418) + g_activeIndex;

    if (entry->firstField != 0) {
        uint8_t outputBuffer[8] = {};           // local_20
        processObjectEntry(g_globalPointer, entry, outputBuffer);
    }
}