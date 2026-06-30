// FUNC_NAME: GlobalFunctions::assignTransformedValue

/**
 * Function at 0x006942a0
 * Takes a pointer to an undefined4 value, applies a transformation function (FUN_00ab3c50)
 * to the current value, stores the result back, and returns the pointer (for chaining).
 * This is likely a utility helper for in-place value transformation, such as encoding,
 * hashing, or clamping a value.
 */
undefined4 * __fastcall assignTransformedValue(undefined4 *valuePtr)
{
    undefined4 transformedResult;
    
    // Call transformation function on current value
    transformedResult = FUN_00ab3c50(*valuePtr);
    
    // Store transformed value back
    *valuePtr = transformedResult;
    
    // Return pointer for chaining (similar to assignment operator returning *this)
    return valuePtr;
}