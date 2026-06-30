// FUNC_NAME: CStringHasher::CalculateAndPrint

void __fastcall CStringHasher::CalculateAndPrint(void* thisPtr, char* inputString) {
    char buffer[12];
    char* strIter;
    char currentChar;
    unsigned int hashValue;

    if (inputString != NULL) {
        // Find end of string
        strIter = inputString;
        while (*strIter != '\0') {
            strIter++;
        }

        // If string length > 11, compute hash on substring from start to length - 4
        if ((int)(strIter - (inputString + 1)) > 11) {
            // param: inputString, inputString + (strlen - 4)  // +0x??? FUN_004dafd0 likely substring hash
            hashValue = FUN_004dafd0(inputString, inputString + (strIter - (inputString + 1) - 3));
            // Format hash as 8-digit hex followed by original string? (buffer is 12 bytes, maybe truncated)
            _sprintf(buffer, "%08x%s", hashValue);
        }
        // Output the result to debug/log system
        FUN_004eafe0();
        return;
    }

    // If input is null, zero out two fields at this+0 and this+4 (underlying structure fields)
    *((int*)thisPtr) = 0;
    *((int*)thisPtr + 1) = 0;
    return;
}