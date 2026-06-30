// FUNC_NAME: Condition::evaluateNotEqual
// Address: 0x006ed0a0
// Role: Evaluates a condition of type bool, int, or float by comparing the result of a type-specific comparison function to a stored reference value. Returns true if the result is not equal to the reference.

// The condition structure is pointed to by this pointer.
// Offsets (in int32 units):
// +0: type (0=bool, 1=int, 2=float)
// +4: operandA (first argument to comparison function)
// +8: operandB (second argument to comparison function)
// +12: referenceValue (stored as int, interpreted according to type)

// External comparison functions (not shown):
// boolCompare(operandA, operandB, context) -> char (bool as char)
// intCompare(operandA, operandB, context) -> int
// floatCompare(operandA, operandB, context) -> float (x87 extended precision)

// Note: The function takes an additional context parameter (param_2) passed to the comparison functions.

bool __thiscall Condition::evaluateNotEqual(int* thisPtr, int context)
{
    int type = *thisPtr;                 // +0x00
    int* operands = thisPtr + 1;         // +0x04, +0x08
    int referenceInt = thisPtr[3];       // +0x0C

    switch (type)
    {
        case 0: // bool comparison
        {
            char compareResult = boolCompare(operands[0], operands[1], context);
            return compareResult != (char)referenceInt;
        }
        case 1: // int comparison
        {
            int compareResult = intCompare(operands[0], operands[1], context);
            return compareResult != referenceInt;
        }
        case 2: // float comparison
        {
            float compareResult = (float)floatCompare(operands[0], operands[1], context);
            float refFloat = (float)referenceInt; // stored as int, interpreted as float
            return compareResult != refFloat;
        }
        default:
            return false;
    }
}