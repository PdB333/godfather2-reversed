// FUNC_NAME: NPC::updateBehavior
// Address: 0x00769ef0
// Called from NPC::update (0x0076a000) to evaluate and set action flags

#include <cstdlib> // for _rand

// External globals (likely set in data section)
extern float MIN_INTERVAL;          // DAT_00e51bc0: minimum time interval for action A
extern float RAND_SCALE;            // DAT_00e44590: scaling factor for rand(), probably 1.0 / RAND_MAX
extern float PROBABILITY_THRESHOLD; // DAT_00d65bc0: probability threshold for action C/D

// Forward declarations of helper functions
float getTimeSinceLastEvent();                    // FUN_00769620
bool canPerformActionA();                         // FUN_007695b0
bool shouldPerformActionB(float elapsedTime);     // FUN_007697a0
bool isInCombatMode();                            // FUN_004ac260
bool isTargetVisible();                           // FUN_00769110
bool isTargetReachable();                         // FUN_00769200
int startAction(int, int, int, float, float);    // FUN_00769400 – returns some handle

// Action flag bits (offset +0x7c = 0x1f*4)
enum ActionFlags : int {
    ACTION_A = 1,  // e.g., chase
    ACTION_B = 2,  // e.g., flee
    ACTION_C = 4,  // e.g., attack from cover
    ACTION_D = 8   // e.g., move to cover
};

// Behavior state constants (offset +0x74 = 0x1d*4)
enum BehaviorState : int {
    STATE_NONE     = 0,
    STATE_INVALID  = 0x48  // 72 – possibly dead or disabled
};

void __fastcall NPC::updateBehavior(int* thisPtr)
{
    // Typedef for readability
    int& state = thisPtr[0x1d];         // +0x74: behavior state
    int& flags = thisPtr[0x1f];         // +0x7c: action flags

    // Clear lower 4 bits (reset all pending actions)
    flags = flags & 0xFFFFFFF0;

    // Only proceed if in a valid state
    if (state == 0 || state == STATE_INVALID) {
        return;
    }

    float elapsedTime = getTimeSinceLastEvent();
    float minInterval = MIN_INTERVAL;

    // Redundant state check from original code
    if (state != 0 && state != STATE_INVALID) {
        int r = _rand();
        // Random offset adds jitter to the minimum interval
        if ((float)r * RAND_SCALE + minInterval < elapsedTime) {
            bool canDoA = canPerformActionA();
            if (canDoA) {
                flags |= ACTION_A;
                return; // higher priority action, exit
            }
        }
    }

    // Second action (B) – not gated by the random/time check
    bool canDoB = shouldPerformActionB(elapsedTime);
    if (canDoB) {
        flags |= ACTION_B;
        return;
    }

    // Check combat mode
    bool isCombat = isInCombatMode();
    if (isCombat) {
        int r2 = _rand();
        // Probability check for actions C or D
        if ((float)r2 * RAND_SCALE <= PROBABILITY_THRESHOLD) {
            bool targetVisible = isTargetVisible();
            if (!targetVisible) {
                flags |= ACTION_C; // e.g., attack from cover
            } else {
                bool targetReachable = isTargetReachable();
                if (!targetReachable) {
                    flags |= ACTION_D; // e.g., move to cover
                }
            }
        }

        // If action C was not taken, perform default action
        if ((flags & ACTION_C) == 0) {
            int vtable = *thisPtr; // vtable pointer at offset 0
            // Start action with parameters (actionType=1, ???, ???, scaleX=1.0, scaleY=1.0)
            int actionHandle = startAction(1, 0, 0, 1.0f, 1.0f);
            // Call virtual function at vtable+0x2c (index 11) to execute the action
            (*(void (__thiscall*)(int)) (vtable + 0x2c))(actionHandle);
        }
    }
}