// FUNC_NAME: ConditionEvaluator::Evaluate
// Function address: 0x00904d20
// Role: Evaluates a condition based on game state flags and a stored condition type.

// Forward declarations for external functions and globals.
extern bool __fastcall IsMenuOpen();           // FUN_008a4380
extern bool __fastcall IsCutscenePlaying();    // FUN_0089c630
extern class GameManager* gGameManager;        // DAT_01223484, singleton pointer

// Condition type enum (offset +0x60)
enum EConditionType : int {
    kCond_GlobalPause        = 0, // return global pause flag
    kCond_MenuOpenNotPaused  = 1, // menu open and game not paused
    kCond_MenuOpen           = 2, // return menu open flag
    kCond_MenuClosed         = 3, // return menu closed flag
    kCond_MenuAndCutscene    = 4  // menu open and cutscene active
};

class ConditionEvaluator {
public:
    EConditionType m_eConditionType; // +0x60

    bool __fastcall Evaluate();        // FUN_00904d20
};

bool __fastcall ConditionEvaluator::Evaluate() {
    // Get the global GameManager singleton
    GameManager* pGameManager = gGameManager;

    // Check global pause state (GameManager +0x08)
    bool bIsPaused = (pGameManager && *(int*)((uint8_t*)pGameManager + 8) != 0);

    // Check menu open state from engine
    bool bMenuOpen = IsMenuOpen();

    // Check cutscene playing state
    bool bCutsceneActive = IsCutscenePlaying();

    switch (m_eConditionType) {
    case kCond_GlobalPause:          // 0
        return bIsPaused;

    case kCond_MenuOpenNotPaused:    // 1
        if (bMenuOpen && !bIsPaused) {
            return true;
        }
        break;

    case kCond_MenuOpen:             // 2
        return bMenuOpen;

    case kCond_MenuClosed:           // 3
        return !bMenuOpen;

    case kCond_MenuAndCutscene:      // 4
        if (bMenuOpen && bCutsceneActive) {
            return true;
        }
        break;
    }

    return false;
}