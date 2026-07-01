// FUNC_NAME: processDebugCommand
// Address: 0x00984ee0
// Role: Handles a debug/cheat command string and processes it based on extracted data and a prefix check.

void processDebugCommand(char* resultStr, char* inputStr, void* contextPtr)
{
    char c;
    char* strPtr;
    int len;
    bool startsWithOne;
    int extractedA, extractedB, extractedC, extractedD; // extracted from context
    int copiedA, copiedB, copiedC, copiedD; // copy for special case

    if (inputStr != nullptr) {
        // Calculate length of inputStr excluding null terminator
        strPtr = inputStr;
        do {
            c = *strPtr;
            strPtr++;
        } while (c != '\0');
        len = (int)(strPtr - (inputStr + 1)); // length without the null

        // Only process if string length > 4
        if (4 < len) {
            // Extract four values from context (likely time/coordinate data)
            FUN_005c50c0(contextPtr, &extractedA, &extractedB, &extractedC, &extractedD);
            // Process the input string with extracted data, storing result in resultStr
            FUN_00926960(inputStr, resultStr, extractedA, extractedB, extractedC, extractedD);

            // Check if resultStr starts with the character '1'
            startsWithOne = true;
            strPtr = "1"; // compare against single character '1'
            int i = 2; // compare up to 2 characters, but we break if mismatch
            do {
                if (i == 0) break;
                i--;
                startsWithOne = (*resultStr == *strPtr);
                resultStr++;
                strPtr++;
            } while (startsWithOne);

            if (startsWithOne) {
                // If resultStr started with '1', copy extracted values and call another handler
                copiedA = extractedA;
                copiedB = extractedB;
                copiedC = extractedC;
                copiedD = extractedD;
                FUN_0098d4b0(inputStr, &copiedA); // second function with the four values
            }
        }
    }
}