// FUNC_NAME: safeDivideAndAssign
void safeDivideAndAssign(int32_t thisPtr) {
    int32_t numerator = getValueByIndex(1);
    int32_t denominator = getValueByIndex(2);
    if (denominator != 0) {
        setDivisionResult(thisPtr, numerator / denominator);
        return;
    }
    printError("Int32 operator / : Tried to divide by zero.");
    // Trigger debug breakpoint
    __asm { int 3 }
}