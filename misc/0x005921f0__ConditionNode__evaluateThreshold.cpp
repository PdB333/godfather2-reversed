// FUNC_NAME: ConditionNode::evaluateThreshold
/* Address: 0x005921f0
 * Role: Compares two condition values (constants or function results).
 * Returns 1 if second value > first value, storing this pointer in output[3].
 */

struct ConditionInput {
    char* first;   // char* to condition data block (type tag + value/index)
    char* second;  // char* to condition data block (type tag + value/index)
};

// Global function table for evaluating indexed conditions
// DAT_01205570: array of function pointers, DAT_01205574: count
extern float (__cdecl *gConditionFunctionTable[])(void* context, int index);
extern int gConditionFunctionCount;

bool __thiscall ConditionNode::evaluateThreshold(void* context, void** output) {
    float value1, value2;
    ConditionInput* inputs = this->m_inputs; // +0x08

    // --- Read first value ---
    char* data1 = inputs->first;
    if (*data1 == '\n') {
        int idx = *(short*)(data1 + 2);
        if (idx >= 0 && idx < gConditionFunctionCount && gConditionFunctionTable[idx] != nullptr) {
            value1 = gConditionFunctionTable[idx](context, idx);
            // Note: The decompiled code passes ( *param_2, iVar3, local_18 ) but param_2 may be context?
            // Actual call: (*pcVar2)(*param_2, iVar3, local_18);
            // param_2 is output pointer, *param_2 is context? We'll assume context = *output.
        }
    } else {
        value1 = *(float*)(data1 + 4);
    }

    // --- Read second value ---
    char* data2 = inputs->second;
    if (*data2 == '\n') {
        int idx = *(short*)(data2 + 2);
        if (idx >= 0 && idx < gConditionFunctionCount && gConditionFunctionTable[idx] != nullptr) {
            value2 = gConditionFunctionTable[idx](context, idx);
        }
    } else {
        value2 = *(float*)(data2 + 4);
    }

    if (value2 <= value1) {
        return false;
    }

    output[3] = this; // Store pointer to this condition if threshold exceeded
    return true;
}