// Xbox PDB: EARS_Apt_UIHud_SetPressureMeterBarColor
// FUNC_NAME: PressureComponent::updateMeterColor
// Function at 0x00939ee0
// Updates the pressure meter color based on submission state and pressure level relative to threshold.
// Called when pressure meter visual needs to change (e.g., during intimidation/fighting minigame).

#include <cstddef>

// Forward declarations of helper functions (not reconstructed here)
bool isSubmissionActive();   // FUN_0078af40 - checks if player/enemy in submission state
bool isPressureBelowThreshold(); // FUN_0078b010 - checks if pressure bar is below some threshold

// External event/setting function (likely from EARS framework)
void fireDebugEvent(const char* eventName, int paramCount, void* dataPtr, int extraParam, const char* stateString);
// FUN_005a04a0 - fires an event like "UpdatePressureMeterColor" with state string

// Global data reference (likely a debug channel or event manager pointer)
extern void* DAT_00d8a64c;

// __thiscall member function (no explicit this parameter)
void PressureComponent::updateMeterColor() {
    bool bSubmission = isSubmissionActive();
    const char* state;

    if (bSubmission) {
        state = "submission";
    } else {
        bool bBelow = isPressureBelowThreshold();
        state = bBelow ? "below" : "above";
    }

    // Notify the system to update the meter color visual
    fireDebugEvent("UpdatePressureMeterColor", 0, &DAT_00d8a64c, 1, state);
}