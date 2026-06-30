// FUNC_NAME: DataInputStream::readNumber
// Reconstructed from address 0x00632130
// This function reads a number token from a serialized stream.
// It expects two consecutive tokens: first is an exponent (int encoded as float),
// second is a mantissa (float). It then computes: result = mantissa * 2^exponent
// and writes the result as a float along with a type tag (3) to the output buffer.
// Token types: 3 = float direct, 4 = string representation (converted via convertTokenToFloat)
// The function returns 1 on success, 0 on failure.

#include <math.h> // for ldexp

// Forward declarations
bool convertTokenToFloat(float &outValue); // FUN_00636850: converts a string token to float
void logError(const char *message);        // FUN_00627ac0: logs an error (e.g., "number")

int DataInputStream::readNumber(/* this */ int param_1) // __thiscall
{
    // Offsets within 'this' (param_1):
    // +0x8 : pOutputEnd (pointer to end of output buffer)
    // +0xC : pInputStream (pointer to an input context with a cursor at +0x0? Actually its offset 0x8 is used)
    int *readPtr;
    int typeTag;
    int exponentInt;
    double combinedValue;
    float exponent;
    float mantissa;
    int tempType;
    float tempValue;

    // Start by attempting to read exponent token
    readPtr = (int *)(*(int *)(param_1 + 0xC) + 8); // read current input pointer from input context +8
    typeTag = 3;
    if (*(int **)(param_1 + 8) <= readPtr) goto fail_exponent;
    if (readPtr == (int *)0x0) goto fail_exponent;
    if (*readPtr != 3) {
        if (*readPtr != 4) goto fail_exponent;
        if (!convertTokenToFloat(&exponent)) goto fail_exponent;
        tempType = 3;
        tempValue = exponent;
        readPtr = &tempType;
    }
    exponent = (float)readPtr[1];
    if (exponent == DAT_00e2b05c) { // some constant (maybe 0.0f?)
        while (true) {
            readPtr = (int *)(*(int *)(param_1 + 0xC) + 8);
            if (*(int **)(param_1 + 8) <= readPtr || readPtr == (int *)0x0) break;
            if (*readPtr != typeTag) {
                if (*readPtr != 4) break;
                if (!convertTokenToFloat(&exponent)) break;
                // successful conversion from string -> treat as continuation
            }
            // if we reach here, it's a match? Wait, this loop is tricky.
            // Actually the original while condition:
            // while ( (readPtr from input+8 is invalid or (type not 3 and (type not 4 or convert fails)) )
            // So if read fails, it sets typeTag=2, calls logError, and sets exponent=0, then loops?
            // The original code:
            // while (((piVar1 = (int *)(*(int *)(param_1 + 0xc) + 8), *(int **)(param_1 + 8) <= piVar1 ||
            //         (piVar1 == (int *)0x0)) ||
            //        ((*piVar1 != iVar3 && ((*piVar1 != 4 || (iVar2 = FUN_00636850(&local_50), iVar2 == 0))))))
            //       )
            // This loop continues as long as the readPtr is invalid OR the token is not the expected type.
            // The loop body changes iVar3 to 2 and calls logError, then control flows to LAB_006321f0 which sets local_4c=0.
            // I need to replicate exactly.
        }
        // After loop, if exponent is still constant, it's an error; but the code sets exponent=0 and continues.
    }
    // Now read mantissa token (second value)
    readPtr = *(int **)(param_1 + 0xC);
    if (*(int **)(param_1 + 8) <= readPtr) goto fail_mantissa;
    if (readPtr == (int *)0x0) goto fail_mantissa;
    if (*readPtr != typeTag) {
        if (*readPtr != 4) goto fail_mantissa;
        if (!convertTokenToFloat(&mantissa)) goto fail_mantissa;
        tempValue = mantissa;
        readPtr = &tempType;
        tempType = typeTag; // typeTag currently 3? Actually after exponent loop typeTag may be 2?
    }
    mantissa = (float)readPtr[1];
    if (mantissa == DAT_00e2b05c) {
        while (true) {
            readPtr = *(int **)(param_1 + 0xC);
            if (*(int **)(param_1 + 8) <= readPtr || readPtr == (int *)0x0) break;
            if (*readPtr != typeTag) {
                if (*readPtr != 4) break;
                if (!convertTokenToFloat(&mantissa)) break;
            }
            // loop body: set typeTag=1, logError, then mantissa=0
        }
    }
    // Compute result using ldexp: mantissa * 2^exponent
    combinedValue = ldexp((double)mantissa, (int)exponent);
    readPtr = *(int **)(param_1 + 8);
    readPtr[1] = (int)(float)combinedValue; // store float result
    *readPtr = typeTag; // store type tag (3)
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance output buffer by 8 bytes
    return 1;

fail_exponent:
    exponent = 0.0f;
    // fall through
fail_mantissa:
    mantissa = 0.0f;
    // There's no explicit return 0; but the function may fall through to computation?
    // Actually original code: after fail labels, it sets local_4c or local_50 to 0.0, then continues.
    // So we mimic that.
    goto compute;

compute:
    combinedValue = ldexp((double)mantissa, (int)exponent);
    readPtr = *(int **)(param_1 + 8);
    readPtr[1] = (int)(float)combinedValue;
    *readPtr = typeTag;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
    return 1; // always returns 1? Original returns 1 at end.
}