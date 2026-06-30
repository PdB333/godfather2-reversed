// FUNC_NAME: ScriptContext::executeBinaryOperation
// Address: 0x00634660
// Role: Evaluates binary arithmetic operations (add, sub, mul, div, pow) on two script values.
// Values are represented as struct { int type; union { float f; int i; }; } (type 3=float, 4=int).
// The 'this' pointer is a script context with stack frame at +0x8 and frame size at +0x1C.
// The result is written to 'result' (pointer passed in EAX; the calling convention is __thiscall but result returned via pointer in EAX).
void __thiscall ScriptContext::executeBinaryOperation(void *this, int *leftOperand, int *rightOperand, int operation, int *result)
{
    int *convertedRight;
    int local_type;
    int local_value;

    // Try to ensure both operands are float (type 3)
    if (*leftOperand == 3) {
        goto bothFloat;
    }
    else if (*leftOperand == 4) {
        // Attempt integer to float conversion
        int success = convertToFloat(&leftOperand); // FUN_00636850
        if (success != 0) {
            // Wrap the converted value (type 3) into a local
            local_type = 3;
            local_value = leftOperand; // Actually leftOperand is now a pointer? Not exactly; the decompiler reuses param_2.
            // The original code sets local_14=3, local_10=param_2, then param_2=&local_14
            // but we'll emulate by creating a temporary.
            // Actually the code jumps to bothFloat after setting param_2.
        }
        else {
            goto typeMismatch;
        }
    }
    else {
        goto typeMismatch;
    }

bothFloat:
    convertedRight = rightOperand;
    if (*rightOperand != 3) {
        if ((*rightOperand != 4) || (int success = convertToFloat(&local_value), success == 0)) { // local_18 was used for conversion result
            goto typeMismatch;
        }
        // Use converted right operand
        local_type = 3;
        local_value = local_value; // Actually local_8 = local_18 (the converted float value)
        convertedRight = &local_type;
    }
    // Now both operands are floats (type 3)
    switch(operation) {
    case 5: // Addition
        result[0] = 3;
        result[1] = *(float *)(convertedRight + 1) + *(float *)(leftOperand + 1);
        return;
    case 6: // Subtraction
        result[0] = 3;
        result[1] = *(float *)(leftOperand + 1) - *(float *)(convertedRight + 1);
        return;
    case 7: // Multiplication
        result[0] = 3;
        result[1] = *(float *)(convertedRight + 1) * *(float *)(leftOperand + 1);
        return;
    case 8: // Division
        result[0] = 3;
        result[1] = *(float *)(leftOperand + 1) / *(float *)(convertedRight + 1);
        return;
    case 9: // Power (function call based)
        {
            int *powFunc = (int *)popStack(); // FUN_00637f90: returns pointer to function?
            int stackSizeBefore = *(int *)((char *)this + 0x1c);
            if (*powFunc != 6) {
                reportError(this, "`__pow' (`^' operator) is not a function"); // FUN_00633920
            }
            callBuiltinFunction(this, powFunc, leftOperand, convertedRight); // FUN_00633ac0
            int *stackTop = *(int **)((char *)this + 8);
            int *resultPtr = (int *)((int)result + (*(int *)((char *)this + 0x1c) - stackSizeBefore));
            resultPtr[0] = stackTop[0];
            resultPtr[1] = stackTop[1];
            return;
        }
    }
    return;

typeMismatch:
    convertedRight = rightOperand;
    int handled = genericBinaryOp(this, leftOperand, rightOperand); // FUN_00633f00
    if (handled == 0) {
        typeErrorOrOperatorNotSupported(this, convertedRight); // FUN_00633790
    }
    return;
}