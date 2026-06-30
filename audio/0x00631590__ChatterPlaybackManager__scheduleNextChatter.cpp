// FUNC_NAME: ChatterPlaybackManager::scheduleNextChatter
// Address: 0x00631590
// Role: Processes the current chatter event (type 3 or 4) and appends a new event with integer-rounded value to the end of the event queue. If the value equals a special constant, it tries to skip to a valid event; otherwise logs an error.

class ChatterPlaybackManager {
    // Queue structure (offsets relative to 'this'):
    // +0x08 : m_pQueueEnd (pointer to end of allocated buffer)
    // +0x0C : m_pCurrentEvent (pointer to the event currently being processed)
    // Event format: 8 bytes, first int32 is type, second float is value
public:
    // Returns 1 on success, 0 on failure (though currently always returns 1)
    int __thiscall scheduleNextChatter() {
        int* pCurrent;         // piVar3
        int* pEnd;             // used as *(int**)(this+8)
        float fValue;          // local_14
        float fRounded;        // fVar4
        float fAdjust;         // fVar5
        int localStack[2];     // local_10, local_c (for temporary event when type==4)

        pCurrent = *(int**)(this + 0x0C);  // +0x0C: current event pointer

        // If the current pointer is invalid (null or beyond end), jump to fallback
        if (pCurrent >= *(int**)(this + 0x08) || pCurrent == nullptr) {
            goto fallback;  // LAB_0063164b
        }

        // Determine if current event is acceptable (type 3 or type 4 with random success)
        if (*pCurrent != 3) {
            if (*pCurrent != 4) {
                goto fallback;  // unknown type
            }
            // Type 4: evaluate random condition
            float randomVal;
            int success = generateRandomValue(&randomVal);  // FUN_00636850
            if (success == 0) {
                goto fallback;
            }
            // Build a temporary event of type 3 using the random value
            localStack[0] = 3;      // type
            localStack[1] = randomVal; // stored as float
            pCurrent = localStack;   // use the temporary event
        }
        // At this point, pCurrent points to an event of type 3 (original or temporary)
        fValue = (float)pCurrent[1];  // get the value

        // If the value equals a special constant, try to find a valid event in the queue
        if (fValue == kSpecialEventValue) {
            // Loop until we find a suitable event (type 3, or type 4 with random success)
            while (true) {
                pCurrent = *(int**)(this + 0x0C);  // re-read current pointer (might have changed? not in this function)
                if (pCurrent >= *(int**)(this + 0x08) || pCurrent == nullptr) {
                    // Invalid pointer - log and break
                    logDebugMessage("number");  // FUN_00627ac0
                    fValue = 0.0f;
                    break;
                }
                if (*pCurrent == 3) {
                    break;  // found type 3
                }
                if (*pCurrent == 4) {
                    int success = generateRandomValue(&fValue);  // reuse fValue as output
                    if (success != 0) {
                        break;  // found type 4 with success
                    }
                }
                // If not found, log and break
                logDebugMessage("number");
                fValue = 0.0f;
                break;
            }
        }

fallback:
        // If we ended up here via goto, fValue remains 0.0f (as set above when needed)
        // Now write a new event of type 3 at the queue end with integer-rounded value

        pEnd = *(int**)(this + 0x08);  // pointer to end of queue
        // Round fValue to the nearest integer using the "magic" float trick
        uint32_t uiValue = (uint32_t)fValue;
        fRounded = (float)(DAT_00e44648 | (DAT_00e44564 & uiValue));
        fRounded = (fValue + fRounded) - fRounded;  // essentially truncates fractional part
        // Compute an adjustment for correct rounding (floor vs nearest)
        fAdjust = (float)(-(uint32_t)((float)(DAT_00e44564 & uiValue) < (fRounded - fValue)) & DAT_00e2b1a4);
        // Write the event: type=3, value = rounded - adjustment (result is integer as float)
        *pEnd = 3;
        pEnd[1] = (int)(fRounded - fAdjust);  // store as float, but actually integer
        // Advance the queue end pointer by 8 bytes
        *(int**)(this + 0x08) = pEnd + 2; // moves by 2 ints (8 bytes)
        return 1;
    }

private:
    // External helper functions (assumed)
    int generateRandomValue(float* outValue);  // FUN_00636850 - returns 1 if success, 0 otherwise
    void logDebugMessage(const char* msg);     // FUN_00627ac0

    // Constants (global variables, replace with actual known names)
    static constexpr float kSpecialEventValue = DAT_00e2b05c; // e.g., 0.0f or -1.0f
    // Magic constants for fast rounding
    static constexpr uint32_t DAT_00e44648 = 0x...; // from binary
    static constexpr uint32_t DAT_00e44564 = 0x...;
    static constexpr uint32_t DAT_00e2b1a4 = 0x...;
};