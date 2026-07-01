// FUNC_NAME: BehaviorComponent::isActionReady
// Function address: 0x007883e0
// Checks if an action is ready based on a timer field at +0x24 and two global thresholds.

extern float __fastcall FUN_00785750(void); // returns some delta (random or time-based)

extern float g_fMinTimeThreshold; // global from _DAT_00d577a0
extern float g_fMaxTimeThreshold; // global from DAT_01205228

bool __fastcall BehaviorComponent::isActionReady(int this) {
    float fCurrentTime = *(float*)(this + 0x24); // +0x24: elapsed time since last action (or distance)
    float fDelta = FUN_00785750();               // additional offset (e.g., random variation)
    if (g_fMinTimeThreshold <= fCurrentTime && (fDelta + fCurrentTime < g_fMaxTimeThreshold)) {
        return true; // action is considered ready
    }
    return false;
}