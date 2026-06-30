// FUNC_NAME: ScriptEngine::executeBinaryOperation
// Address: 0x00634660
// Role: Executes binary arithmetic operations (add, sub, mul, div, pow) on script values.
// Types: 3 = float, 4 = string (converted to float)

#include <cmath>

// Forward declarations of helper functions (assumed from other Ghidra exports)
bool convertStringToFloat(ScriptValue* value);                  // FUN_00636850
ScriptValue* getPowFunction();                                  // FUN_00637f90
void reportError(ScriptEngine* self, const char* message);      // FUN_00633920
void callBuiltinFunction(ScriptEngine* self, ScriptValue* func, ScriptValue* left, ScriptValue* right); // FUN_00633ac0
bool attemptDefaultOperation(ScriptEngine* self, ScriptValue* left, ScriptValue* right); // FUN_00633f00
void typeMismatchError(ScriptEngine* self, ScriptValue* left);  // FUN_00633790

struct ScriptValue {
    int type;   // 0x00: type tag
    float value; // 0x04: numeric value (as float bits)
};

void __thiscall ScriptEngine::executeBinaryOperation(ScriptEngine* this,
                                                     ScriptValue* result,
                                                     ScriptValue* left,
                                                     ScriptValue* right,
                                                     int operation)
{
    ScriptValue* leftOp = left;
    ScriptValue* rightOp = right;

    // Ensure left operand is float; if string, try to convert
    if (left->type == 3) { // FLOAT
        // fall through to common code
    }
    else if (left->type == 4) { // STRING
        ScriptValue converted;
        if (convertStringToFloat(&converted)) {
            leftOp = &converted; // converted is a local float
            goto common;
        }
        goto error;
    }
    else {
        goto error;
    }

common:
    // Ensure right operand is float; if string, try to convert
    if (right->type == 3) {
        rightOp = right;
    }
    else if (right->type == 4) {
        ScriptValue converted;
        if (convertStringToFloat(&converted)) {
            rightOp = &converted;
        }
        else {
            goto error;
        }
    }
    else {
        goto error;
    }

    // Perform the operation based on opcode
    switch (operation) {
    case 5: // ADD
        result->type = 3;
        result->value = leftOp->value + rightOp->value;
        return;
    case 6: // SUB
        result->type = 3;
        result->value = leftOp->value - rightOp->value;
        return;
    case 7: // MUL
        result->type = 3;
        result->value = leftOp->value * rightOp->value;
        return;
    case 8: // DIV
        result->type = 3;
        result->value = leftOp->value / rightOp->value;
        return;
    case 9: // POW
        {
            // Get the pow function (type 6 = function)
            ScriptValue* powFunc = getPowFunction();
            if (powFunc->type != 6) {
                reportError(this, "`__pow' (`^' operator) is not a function");
            }
            // Call the builtin pow function with left and right
            int stackBefore = *(int*)((char*)this + 0x1c); // stack pointer before call
            callBuiltinFunction(this, powFunc, leftOp, rightOp);
            // Retrieve result from stack
            ScriptValue* stackTop = *(ScriptValue**)((char*)this + 8);
            int stackAfter = *(int*)((char*)this + 0x1c);
            int bytesPushed = stackAfter - stackBefore;
            ScriptValue* resultOnStack = (ScriptValue*)((char*)result + bytesPushed);
            *resultOnStack = *stackTop;
        }
        return;
    }
    return;

error:
    // Attempt default operation (maybe string concatenation)
    if (attemptDefaultOperation(this, left, right)) {
        return;
    }
    typeMismatchError(this, left);
}