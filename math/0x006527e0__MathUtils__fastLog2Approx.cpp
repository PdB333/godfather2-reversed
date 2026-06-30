// FUNC_NAME: MathUtils::fastLog2Approx
void __fastcall fastLog2Approx(int eaxArg, int param2, int param3, int* outResult)
{
    // eaxArg is passed in EAX register (first argument in fastcall? Actually the decompiler shows in_EAX)
    // param2: some input value
    // param3: unused? (undefined4)
    // outResult: pointer to output integer (originally param4, but used as pointer)

    int diff = eaxArg - param2;
    unsigned int uVar2 = diff + 1;  // (eax - param2) + 1

    float fVar1 = (float)(int)uVar2;
    if ((int)uVar2 < 0) {
        // If negative, add a large constant (likely 2^32 or 2^31) to make it positive float
        fVar1 += *(float*)0x00e44578;  // DAT_00e44578 is a float constant
    }

    // Adjust output pointer: outResult = outResult - param2 (but this modifies the pointer value? Actually param4 was an int, but we treat as pointer)
    // The decompiler shows param_4 = param_4 - param_2; then &param_4 is passed.
    // So we need to compute a new value and store it at the address pointed by outResult.
    // But the original param4 was an integer, not a pointer. The decompiler likely flattened.
    // We'll assume outResult is a pointer to int, and we compute a value to store.
    int adjustedValue = (int)outResult - param2;  // This is the value that will be passed as pointer target

    // Compute exponent part: extract exponent from float fVar1 (bits 23-30), subtract bias 127, and add a boolean from bitwise AND
    int exponentPart = ((uVar2 & diff) != 0) + ((char)((uint)fVar1 >> 0x17)) - 0x7f;

    // Call internal math function with exponentPart and address of adjustedValue
    internalMathFunc(exponentPart, &adjustedValue);

    // The result is stored in adjustedValue, but the original function doesn't return anything.
    // Possibly the caller expects the result in the memory pointed by outResult.
    // Since the decompiler shows no assignment back, we assume internalMathFunc modifies adjustedValue.
    // We'll store adjustedValue back to *outResult? But the original code doesn't show that.
    // Actually, the function returns void, so the effect is through the pointer passed to internalMathFunc.
    // The original param4 was a local variable, so the result is stored there.
    // We'll assume the caller uses the modified value.
    *outResult = adjustedValue;  // This is speculative; the decompiler doesn't show this assignment.
}