// FUNC_NAME: SomeClass::constructWithParameters
// Purpose: Likely constructs an object from parameters, possibly setting a string from two parts.
// Address: 0x0082b2b0
// Calling convention: __thiscall (this in ecx, explicit parameters as shown)
// Note: The function uses two temporary local buffers (128 and 140 bytes) to build intermediate strings.
// Then calls three internal functions: extractFirstPart, concatenateParts, and assignToThis.
// The exact semantics of param_3 and param_4 are unclear; they may act as indices, lengths, or flags.

__thiscall SomeClass* SomeClass::constructWithParameters(SomeClass* this,
                                                         int param_2,          // May be a source string or identifier
                                                         int param_3,          // Possibly a position/index
                                                         int param_4)          // Possibly a count/flag
{
    char firstPart[128];   // Buffer for first part (128 bytes)
    char secondPart[140];  // Buffer for concatenated result (140 bytes)
    int intermediateResult;

    // Step 1: Build first part from param_4 and param_3 into firstPart
    intermediateResult = extractFirstPart(firstPart, param_4, param_3);

    // Step 2: Concatenate param_2 with the first part into secondPart
    intermediateResult = concatenateParts(secondPart, param_2, intermediateResult);

    // Step 3: Assign the combined result to this object (using param_3 as additional info)
    assignToThis(this, param_3, intermediateResult);

    return this;
}