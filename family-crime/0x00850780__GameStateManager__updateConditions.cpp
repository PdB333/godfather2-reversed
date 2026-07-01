// FUNC_NAME: GameStateManager::updateConditions

void __fastcall GameStateManager::updateConditions(void* this) // param_1 = this
{
    float ratio;
    
    // Check if some global condition prevents update (e.g., loading or paused)
    // DAT_011299bc likely points to a GameState or CutsceneManager singleton
    // +0x1c: bool indicating something active
    if (*(int*)(DAT_011299bc + 0x1c) != 0) {
        return;
    }
    
    // Set a flag to indicate this update is happening
    DAT_0112ddc0 = 1;
    
    // Call some initialization or audio event (FUN_0068c590 with arg 0)
    FUN_0068c590(0);
    
    // DAT_01223394 points to a major game object (e.g., Player, WorldController)
    // +0x54: byte flag, possibly "isTutorialActive" or "isCutsceneActive"
    if (*(char*)(DAT_01223394 + 0x54) == '\0') {
        // Normal path: update HUD/mission UI and continue
        FUN_0084fe80(); // likely showHUD or updateMissionUI
        FUN_0084ff70(); // likely updateState
        goto LAB_00850823;
    }
    
    // Tutorial/cutscene path: need to check progress
    // +0x5c: float current value (e.g., health, progress)
    // +0x70: float max value (e.g., max health, required progress)
    // +0x58: int flag indicating some condition
    if (*(float*)(DAT_01223394 + 0x5c) <= *(float*)(DAT_01223394 + 0x70)) {
        if (*(int*)(DAT_01223394 + 0x58) != 0) goto LAB_0085080c;
    } else {
        // Calculate ratio of current to max
        ratio = *(float*)(DAT_01223394 + 0x70) / *(float*)(DAT_01223394 + 0x5c);
        // If flag is set, invert the ratio relative to 1.0
        if (*(int*)(DAT_01223394 + 0x58) != 0) {
            ratio = _DAT_00d5780c - ratio; // _DAT_00d5780c likely 1.0f
        }
        if (ratio < _DAT_00d5780c) {
LAB_0085080c:
            // Trigger a mission or event: set this->field at +0x84 to 1
            *(int*)(this + 0x84) = 1;
            // Activate a specific mission/tutorial event
            FUN_00408680(&DAT_012069c4); // DAT_012069c4 is a global event/state identifier
            goto LAB_00850823;
        }
    }
    
    // Fallback: call other update functions if condition not met
    FUN_0084fe80();
    FUN_008506f0();
    
LAB_00850823:
    // Post-update: activate another state (e.g., timer or event queue)
    FUN_00408680(&DAT_0112ddd8);
    
    // Prepare a short-lived timer or event data and schedule it
    // local_c = DAT_011303c8 (some constant), local_8 = 0, local_4 = 0
    struct {
        float someValue;   // offset 0
        int zero;          // offset 4
        char padding;      // offset 8
    } timerData;
    timerData.someValue = DAT_011303c8; // probably a floating-point constant
    timerData.zero = 0;
    timerData.padding = 0;
    FUN_00408a00(&timerData, 0); // likely registers or starts a timer
    return;
}