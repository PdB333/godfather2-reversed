// FUNC_NAME: ScriptExpressionEvaluator::convertToUInt32
uint32_t ScriptExpressionEvaluator::convertToUInt32(int32_t index)
{
    // Try direct lookup: get stored UInt32 value by index (e.g., from constant table)
    uint32_t *storedValue = (uint32_t *)getTypeInfo(index, "UInt32");
    if (storedValue != nullptr)
    {
        return *storedValue;
    }

    // If index is out of range or less than 1, attempt to convert from current stack
    if (index < 1)
    {
        // Retrieve current evaluation stack frame
        int32_t *stackFrame = (int32_t *)getCurrentStackFrame();
        // Check if the top of stack is of type 3 (probably float)
        if (stackFrame != nullptr && *stackFrame == 3)
        {
            double fValue = (double)popStackFloat();
            return static_cast<uint32_t>(std::round(fValue));
        }
    }
    else
    {
        // Bounds check: fetch variable array pointer from this+0x0C and this+0x08
        int32_t *arrayStart = *(int32_t **)(this + 0x0C);  // base of variable storage
        int32_t *arrayEnd   = *(int32_t **)(this + 0x08);  // one past last valid element
        int32_t *candidate  = arrayStart - 8 + index * 8;   // each entry is 8 bytes, index is 1-based

        // If candidate lies within the valid range, attempt stack conversion as above
        if (candidate < arrayEnd)
        {
            // Same conversion logic as the index < 1 branch
            int32_t *stackFrame = (int32_t *)getCurrentStackFrame();
            if (stackFrame != nullptr && *stackFrame == 3)
            {
                double fValue = (double)popStackFloat();
                return static_cast<uint32_t>(std::round(fValue));
            }
        }
    }

    // Fallback: attempt to get the expression string (e.g., the literal being converted)
    const char *exprString = getExpressionString();
    if (exprString == nullptr)
    {
        initExpression();
        exprString = getExpressionString();
        if (exprString == nullptr)
        {
            exprString = "<null>";
        }
    }

    // Check if conversion is blocked by a flag (e.g., during error recovery)
    if (isConversionBlocked())
    {
        return 0;
    }

    // Log error and abort
    logError("Could not turn '%s' into an UInt32.\n", exprString);
    // Trigger a software interrupt (likely a debug break or exception)
    uint32_t (*exceptionHandler)() = (uint32_t (*)())swi(3);
    return exceptionHandler();
}