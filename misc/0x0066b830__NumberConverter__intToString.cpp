// FUNC_NAME: NumberConverter::intToString
// Address: 0x0066b830
// Converts an integer to a null-terminated string in a given buffer.
// Handles negative numbers by prepending '-'.
// Returns 0 on success, -3 if buffer too small, or error codes from digit conversion.
// Uses internal lock (FUN_006677e0 / FUN_00665b40) for thread safety.

int NumberConverter::intToString(char* buffer, int bufferSize) {
    char* writePtr = buffer;
    // Max supported buffer size is 64 (0x40)
    if (bufferSize - 2 > 0x3e) {
        return -3;  // Buffer too small
    }

    // If the number (stored in this->number) is non-zero, do conversion.
    if (this->number != 0) {
        // Acquire internal lock
        if (FUN_006677e0() == 0) {
            char* current = buffer;
            // If number is negative, insert '-'
            if (this->isNegative) {
                *current = '-';
                current++;
                this->isNegative = 0;
            }

            // Convert digits. The digit array (local_10) is used by the conversion routine.
            int digitStack[2];  // local_10
            while (digitStack[0] != 0) {
                int err = FUN_00666670(digitStack, bufferSize, digitStack, &buffer);  // Convert next digit
                if (err != 0) {
                    FUN_00665b40();  // Release lock
                    return err;
                }
                *current = *((char*)0x0e440d8 + (int)buffer);  // Write digit character from global digit table
                current++;
            }

            FUN_0066bb10();  // Ensure null-terminated

            *current = '\0';
            FUN_00665b40();  // Release lock
            return 0;
        }
        return iVar3;
    }

    // If number is zero, just write '0' and null terminator
    *buffer = '0';
    *(buffer + 1) = '\0';
    return 0;
}