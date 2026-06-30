// FUNC_NAME: StepState::update
class StepState {
public:
    // +0x00: current state (0,1,2)
    int m_state;
    // +0x04: index into step array
    int m_stepIndex;

    void update(int stepArrayBase, int callContext) {
        int state = m_state;
        if (state == 0) {
            // state 0: no operation
            return;
        }
        if (state == 1) {
            // state 1: guard on stepIndex being zero (skip)
            if (m_stepIndex == 0) {
                return;
            }
            return;
        }
        if (state == 2) {
            // state 2: advance to a specific step entry
            // Each entry is 0x14 (20) bytes
            // Step offset: (stepIndex + 0xC) * 0x14
            int stepOffset = (m_stepIndex + 0xC) * 0x14;
            int* stepEntry = (int*)(stepArrayBase + stepOffset);
            // stepEntry[1] (offset +4) is a pointer to an object with a vtable
            int* stepObject = (int*)stepEntry[1];
            if (stepObject != 0) {
                // vtable[0x2c] is a callback taking (callContext, int* result)
                int resultPlaceholder = 0;
                void (*callback)(int, int*) = (void (*)(int, int*))(*(int**)(stepObject[0]) + 0x2c);
                callback(callContext, &resultPlaceholder);
            }
            return;
        }
        // unknown state, fall through
    }
};