// FUN_00587a00: EvaluatorContext::findMatchingAction
// Reconstructed from Ghidra decompilation
// Role: Iterates over a list of action/condition items, finds one whose range includes a value from the context, and dispatches based on type character.

class ConditionManager; // forward declaration

class EvaluatorContext {
public:
    // +0x00: pointer to owning object (used to access ConditionManager)
    void* m_owner; // *param_1
    // +0x04: pointer to a context structure that holds e.g. current value, etc.
    void* m_context; // param_1[1]
    // +0x08: additional parameter
    int m_param; // param_1[2]
    // output fields:
    // +0x0C: pointer to matched item
    void* m_resultItem; // param_1[3]
    // +0x10: byte result (type?)
    char m_resultByte; // *(char *)(param_1 + 4)
    // +0x14: integer result
    int m_resultInt; // param_1[5]

    int findMatchingAction(); // returns -1 if no match, 0 or item-specific value on match
};

// External functions (known callees)
void resetConditionManager(); // FUN_005878e0
int computeOffset(int base, int value); // FUN_00587c60 - returns some offset
void* getNextItem(); // FUN_00587bb0 - iterator, returns next item or 0

// Global variable
extern float g_scaleFactor; // DAT_00e2b1a4

int EvaluatorContext::findMatchingAction() {
    // Dereference to get ConditionManager pointer
    // *(int *)(*(int *)(*(int *)(m_owner) + 0x70) + 0x2c) -> conditionManager
    ConditionManager* condMgr = (ConditionManager*)(*(int*)(*(int*)(m_owner) + 0x70) + 0x2c);
    if (condMgr == nullptr) {
        return -1;
    }

    // If the manager is flagged as active, reset it
    if (*(char*)(condMgr + 0x10) != '\0') {
        resetConditionManager();
    }

    // Fetch context fields
    int contextValue = *(int*)(m_context + 0x14);          // local_10
    int base = *(int*)(condMgr + 0x4);                     // iVar2
    int count = *(int*)(condMgr + 0xC);                    // iVar5
    int zero = 0;
    int offset = computeOffset(base, contextValue);        // local_8
    int endAddr = base + count * 4;                        // local_4 (seems unused?)

    // Iterate through items
    int* item = (int*)getNextItem();
    while (item != nullptr) {
        int flags = item[0xB];                             // piVar4[0xb] (offset 0x2C)
        bool useAlt = (flags & 0x20) && (*item < 2);      // uVar7 condition
        int valueIfHit;                                    // iVar5 (local result)

        int thresholdLow, thresholdHigh;                   // fVar10, fVar9
        if (useAlt) {
            // Alternative thresholds from offsets 3 and 4
            thresholdLow = item[3];
            thresholdHigh = item[4];
            valueIfHit = item[7];                          // piVar4[7]
        } else {
            // Primary thresholds from offsets 1 and 2
            thresholdLow = item[1];
            thresholdHigh = item[2];
            valueIfHit = item[5];                          // piVar4[5]
        }

        if (valueIfHit == -1) continue;                    // skip invalid entries

        // Pointer to type string
        char* typeStr;
        if (useAlt) {
            typeStr = (char*)item[6];                      // piVar4[6]
        } else {
            typeStr = (char*)item[4];                      // piVar4[4]
        }
        if (typeStr == nullptr) continue;

        // Current value from context
        float currentValue = *(float*)(m_context + 0x1C);  // fVar1

        // Possibly scale thresholds
        if ((flags >> 3) & 1) {
            float scale = *(float*)(m_context + 0x24) - g_scaleFactor; // fVar8
            thresholdLow = (int)(scale * (float)thresholdLow);
            thresholdHigh = (int)(scale * (float)thresholdHigh);
        }

        // Check if current value is within range
        if ((float)thresholdLow <= currentValue && currentValue <= (float)thresholdHigh) {
            // Prepare dispatch arguments
            int dispatchArgs[2] = { this->m_owner, this->m_param }; // local_20, local_1c
            char dispatchType = *typeStr;
            if (dispatchType < 0x0A) { // newline check? likely '<'
                // Table of dispatch functions indexed by type character
                typedef int (*DispatchFunc)(int*);
                extern DispatchFunc PTR_FUN_0103af90[10]; // from data
                DispatchFunc func = PTR_FUN_0103af90[dispatchType];
                if (func(dispatchArgs) != 0) {
                    // Set output fields
                    this->m_resultItem = item;
                    this->m_resultByte = 0;                // local_18 = 0
                    this->m_resultInt = 0;                 // local_14 = 0
                    // If using alt flags, return specific value
                    if ((flags & 0x20) && (*item > 3)) {
                        return item[5];                    // piVar4[5]
                    }
                    return 0;
                }
            }
        }

        item = (int*)getNextItem();
    }

    return -1;
}