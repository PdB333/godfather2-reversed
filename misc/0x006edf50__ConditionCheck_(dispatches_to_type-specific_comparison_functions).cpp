// FUNC_NAME: ConditionCheck (dispatches to type-specific comparison functions)
// Address: 0x006edf50
// Role: Evaluates a condition represented as a struct with type (0=char,1=int,2=float) and two operands, plus an external parameter.
// Returns true if the type-specific function returns 0.

// External function declarations (actual implementations not shown)
extern char __cdecl compareChar(int operandA, int operandB, int externalParam);
extern int  __cdecl compareInt(int operandA, int operandB, int externalParam);
extern float __cdecl compareFloat(int operandA, int operandB, int externalParam);

bool __cdecl ConditionCheck(int* condition, int externalParam)
{
    int type = condition[0];          // +0x00: condition type
    int operandA = condition[1];      // +0x04: first operand
    int operandB = condition[2];      // +0x08: second operand

    bool result = false;

    if (type == 0)
    {
        // Char comparison – returns 0 if condition holds
        char cmpResult = compareChar(operandA, operandB, externalParam);
        result = (cmpResult == '\0');
    }
    else if (type == 1)
    {
        // Int comparison – returns 0 if condition holds
        int cmpResult = compareInt(operandA, operandB, externalParam);
        result = (cmpResult == 0);
    }
    else if (type == 2)
    {
        // Float comparison – returns 0.0f if condition holds
        float cmpResult = compareFloat(operandA, operandB, externalParam);
        result = (cmpResult == 0.0f);
    }

    return result;
}