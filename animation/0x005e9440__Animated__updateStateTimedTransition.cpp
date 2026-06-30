// FUNC_NAME: Animated::updateStateTimedTransition
// Address: 0x005e9440
// Uses global: DAT_00e2e230 (time scale factor), DAT_01223518+8 (base value)
// callees: 0x005dbc10 (math function), 0x005e8900 (state eligibility check)

class Animated;

// External math function (sin/cos/lerp? takes float->double)
extern "C" void someMathFunction(double input);

// External eligibility check for state transition
extern "C" int checkTransitionEligibility(void);

// The class likely has a state machine with fields:
// +0x1b8 = m_targetValue (int)
// +0x1dc = m_previousValue (int) - copy of +0x1d8
// +0x1bc = m_blendReset (byte? set to 0)
// +0x204 = m_baseValue (int)
// +0x210 = m_someTimer (int)
// +0x285 = m_flag1 (bool)
// +0x286 = m_flag2 (bool)
// +0x480 = m_previousState (int)
// +0x484 = m_state (int)  (1=idle, 2=walk, 3=run, 4=other)

struct AnimationInputData {
    float m_timeFactor;        // +0x04
    char pad_08[4];
    int m_doTransition;        // +0x0C (nonzero to confirm and reset timer)
};

int __thiscall Animated::updateStateTimedTransition(Animated* this, AnimationInputData* inputData) {
    float timeFactor = inputData->m_timeFactor;
    int* thisPtr = reinterpret_cast<int*>(this);
    int* inputDataPtr = reinterpret_cast<int*>(inputData);

    // Call math function (e.g., sin/cos on time to produce interpolation factor)
    someMathFunction(static_cast<double>(timeFactor));

    int currentState = thisPtr[0x484 / 4]; // +0x484

    // Check if state is one of: 4,1,2,3
    if (currentState == 4 || currentState == 1 || currentState == 2 || currentState == 3) {
        // Compute new target value from time factor multiplied by global scale
        int newTarget = static_cast<int>(timeFactor * DAT_00e2e230);
        int baseField = *(reinterpret_cast<int*>(DAT_01223518) + 2); // +8 bytes from global

        // If state is not 3, or if the condition holds (target relative to base)
        if (currentState != 3 ||
            newTarget < (thisPtr[0x1b8 / 4] - baseField) + thisPtr[0x204 / 4]) {
            // Set baseField into +0x204, and store newTarget into +0x1b8
            thisPtr[0x204 / 4] = baseField;
            thisPtr[0x1b8 / 4] = newTarget;
        }

        // Copy +0x1d8 to +0x1dc (save previous target)
        thisPtr[0x1dc / 4] = thisPtr[0x1d8 / 4];

        // Reset blend flags
        thisPtr[0x1bc / 4] = 0;    // +0x1bc
        *reinterpret_cast<char*>(thisPtr + 0x285 / 4) = 0; // +0x285
        *reinterpret_cast<char*>(thisPtr + 0x286 / 4) = 0; // +0x286

        // If state is not 3, transition to state 3
        if (currentState != 3) {
            thisPtr[0x484 / 4] = 3;
            if (checkTransitionEligibility()) {
                thisPtr[0x480 / 4] = thisPtr[0x484 / 4]; // copy state to previousState
            }
        }

        // If input data says to finalize transition, clear timer and return
        if (inputData->m_doTransition != 0) {
            thisPtr[0x210 / 4] = 0; // +0x210
            return 1;
        }
    }
    return 1;
}