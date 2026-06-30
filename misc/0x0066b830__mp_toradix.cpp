// Xbox PDB: mp_toradix
// FUNC_NAME: intToString (likely custom integer to string conversion)
int __cdecl intToString(char* buffer, int bufferSize, int* valuePtr) {
    // valuePtr is passed in EAX (register), buffer and bufferSize on stack
    int value = *valuePtr;

    // Check buffer size: must be at least 2 (for sign and terminator) and at most 64 (max digits)
    if (bufferSize - 2U > 0x3e) { // bufferSize < 2 or > 64
        return -3;
    }

    if (value == 0) {
        buffer[0] = '0';  // 0x30
        buffer[1] = 0;
        return 0;
    }

    // Prepare absolute value and detect sign; sets a global/static flag for negative
    int error = prepareAbsoluteAndSign(); // FUN_006677e0
    if (error != 0) {
        return error;
    }

    int isNegative = 0; // local_8, but decompiler shows it uninitialized; assume set by prepareAbsoluteAndSign or global
    // If negative flag is set, write '-' and advance
    if (isNegative == 1) {
        *buffer = '-';  // 0x2d
        buffer++;
        isNegative = 0;
    }

    char* writePtr = buffer; // puVar1
    int currentValue[2] = {value, 0}; // local_10, first element holds remaining quotient

    // Extract digits from least significant to most
    while (currentValue[0] != 0) {
        // FUN_00666670: extracts next digit, stores in currentValue[1], updates quotient
        int err = extractDecimalDigit(currentValue, bufferSize, currentValue, &buffer);
        if (err != 0) {
            releaseLock(); // FUN_00665b40
            return err;
        }
        // Digit character from global array at 0xe440d8 (likely "0123456789")
        *writePtr = digitChars[currentValue[1]]; // originally param_1[0xe440d8]
        writePtr++;
    }

    // FUN_0066bb10: reverse the string in place (since digits were written backwards)
    reverseString(buffer, writePtr - buffer); // approximate

    *writePtr = 0; // null terminator
    releaseLock(); // FUN_00665b40
    return 0;
}