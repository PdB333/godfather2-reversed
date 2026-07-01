// FUNC_NAME: PlayerObjectiveManager::evaluateCondition
// Address: 0x007d1ab0
// Role: Evaluates a condition based on a float member at +0x30 and several global thresholds.
// Returns 1 if condition is met, 0 otherwise.

// Global thresholds (likely set from config or game state)
extern float g_ThresholdA;       // _DAT_00d577a0
extern float g_ThresholdB;       // _DAT_00e5301c
extern float g_ThresholdC;       // _DAT_0112baa4
extern float g_ThresholdD;       // _DAT_00e53020
extern float g_ThresholdE;       // DAT_00e53024

// Internal helper functions (renamed from their addresses)
void __fastcall updateFrameTimer();            // FUN_007ab110
char __fastcall isStoryFlagSet();              // FUN_004ac260
char __fastcall isTutorialActive(int param);   // FUN_0054f460 (param=0)
void __fastcall getPlayerStrength(float* out); // FUN_0054be20 (writes to out)

bool __fastcall PlayerObjectiveManager::evaluateCondition(void* thisPtr) {
    float memberFloat = *(float*)((char*)thisPtr + 0x30); // e.g., current distance or time
    float localStrength;
    float* pStrength = &localStrength; // placeholder, function writes to it

    updateFrameTimer();

    if (g_ThresholdA < memberFloat) {
        // Check if memberFloat exceeds thresholdB or (thresholdC and story flag)
        if (g_ThresholdB <= memberFloat ||
            (g_ThresholdC <= memberFloat && isStoryFlagSet())) {
            return true;
        }

        // Otherwise, check thresholdD and tutorial/strength condition
        if (g_ThresholdD <= memberFloat &&
            !isTutorialActive(0) &&
            // After getPlayerStrength, localStrength is set
            (getPlayerStrength(pStrength), localStrength <= g_ThresholdE)) {
            return true;
        }
    }
    return false;
}