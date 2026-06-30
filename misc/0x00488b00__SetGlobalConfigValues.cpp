// FUNC_NAME: SetGlobalConfigValues
// Address: 0x00488b00
// Role: Sets four global uint32 values from a pointer, optionally triggering an apply function.

// Global variables (likely stored in .data section)
extern uint32_t g_configValue0;   // Address: 0x01163da4
extern uint32_t g_configValue1;   // Address: 0x01163da0
extern uint32_t g_configValue2;   // Address: 0x01163d9c
extern uint32_t g_configValue3;   // Address: 0x01163d98

// Forward declaration of function called when param_2 is true
void ApplyConfigValues(); // Address: 0x00487b30

void SetGlobalConfigValues(uint32_t* source, bool shouldApply)
{
    if (shouldApply != false) {
        ApplyConfigValues();
        return;
    }

    uint32_t value = *source;
    g_configValue0 = value;
    g_configValue1 = value;
    g_configValue2 = value;
    g_configValue3 = value;
}