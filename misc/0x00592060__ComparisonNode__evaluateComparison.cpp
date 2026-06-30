// FUNC_NAME: ComparisonNode::evaluateComparison
// Address: 0x00592060
// Evaluates two operand expressions (either direct float or registered function calls) and returns a comparison result.
// This function is part of the expression system (likely used for condition checks in scripts or behavior trees).
// It compares the values of two operand nodes, encoded as strings starting with '\n' (calling an indexed function) or direct floats.
// The result encodes: equality (bit 6), NaN (bit 2), less-than (bit 1), and additional flags from the second operand's high word.
// If equal, returns the result shifted left by 8; otherwise, writes the current node pointer to context[3] and returns a combined value.

#include <cmath>

// Global function table: indexed by 2-byte indices, each entry is 12 bytes (function pointer at offset 4)
extern void* gFunctionTable; // Actually DAT_01205570
extern int gFunctionTableEntryCount; // DAT_01205574

// Forward declaration of the function called from the table (returns void, but writes float array)
typedef void (*RegisteredFunction)(void* context, int index, float* outValues);

int __thiscall evaluateComparison(int thisPtr, void* context) { // param_1 = this, param_2 = context (undefined4*)
    // Assuming thisPtr points to a comparison node with two operand slots:
    // +0x08: pointer to a structure containing two operand descriptors (each a pointer to data)
    // Operand descriptor at +0x??: likely two pointers: first operand data at offset 0, second at offset 4

    // Read first operand data pointer
    char* operandData1 = *(char**)(*(int*)(thisPtr + 8)); // First operand data
    float leftValue[3]; // Used only [0]

    if (*operandData1 == '\n') {
        // Call registered function to evaluate first operand
        short opIndex = *(short*)(operandData1 + 2);
        if (opIndex >= 0 && opIndex < gFunctionTableEntryCount) {
            RegisteredFunction func = *(RegisteredFunction*)(gFunctionTable + 4 + opIndex * 12);
            if (func != nullptr) {
                func(context, opIndex, leftValue);
            }
        }
    } else {
        // Direct float: float is stored at offset 4 of the operand data
        leftValue[0] = *(float*)(operandData1 + 4);
    }

    // Read second operand data pointer (offset 4 from the first descriptor)
    char* operandData2 = *(char**)(*(int*)(thisPtr + 8) + 4);
    float rightValue[3]; // Used only [0]

    if (*operandData2 == '\n') {
        short opIndex2 = *(short*)(operandData2 + 2);
        if (opIndex2 >= 0 && opIndex2 < gFunctionTableEntryCount) {
            RegisteredFunction func = *(RegisteredFunction*)(gFunctionTable + 4 + opIndex2 * 12);
            if (func != nullptr) {
                func(context, opIndex2, rightValue);
            }
        }
    } else {
        rightValue[0] = *(float*)(operandData2 + 4);
    }

    // Build comparison result flags
    int resultFlags = 0;
    if (leftValue[0] == rightValue[0]) resultFlags |= (1 << 6);   // equality
    if (std::isnan(leftValue[0]) || std::isnan(rightValue[0])) resultFlags |= (1 << 2); // NaN
    resultFlags |= 2; // always set bit 1? (2U) likely a predefined flag
    if (leftValue[0] < rightValue[0]) resultFlags |= 1;            // less-than

    // Embed high 16 bits of the second operand pointer? (decompiler artifact, likely used as additional tag)
    uint shortTag = (uint)operandData2 >> 16;
    uint combined = ((uint)resultFlags) | (shortTag << 16); // CONCAT21

    if (leftValue[0] == rightValue[0]) {
        return combined << 8; // shift left 8 when equal (maybe indicates exact match)
    } else {
        // Write back the current node pointer to context[3] (likely for error reporting or callbacks)
        ((int*)context)[3] = thisPtr;
        return combined | 1; // set lowest byte to 1 (result valid?)
    }
}