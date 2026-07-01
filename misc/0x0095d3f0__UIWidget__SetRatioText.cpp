// FUNC_NAME: UIWidget::SetRatioText
void __thiscall UIWidget::SetRatioText(int thisPtr, char* outputBuffer, uint bufferSize) {
    int denominator = *(int*)(thisPtr + 0x18);
    float ratio;
    if (denominator == 0) {
        ratio = 0.0f;
    } else {
        int numerator = *(int*)(thisPtr + 0x14);
        float fNumerator = (float)numerator;
        if (numerator < 0) {
            fNumerator = fNumerator + 4294967296.0f; // 2^32, convert signed->unsigned float
        }
        float fDenominator = (float)denominator;
        if (denominator < 0) {
            fDenominator = fDenominator + 4294967296.0f;
        }
        ratio = fNumerator / fDenominator;
    }

    char* stringPtr = nullptr;
    uint local_c = 0;
    uint local_8 = 0;
    void (*deallocFunc)(char*) = nullptr;

    // Convert float to string with 2 decimal places
    FloatToString(ratio, 2, &stringPtr, 1); // FUN_00603da0

    char* displayStr = stringPtr;
    if (stringPtr == nullptr) {
        displayStr = ""; // DAT_0120546e likely empty string
    }

    SetText(outputBuffer, displayStr, bufferSize, local_c); // FUN_005c4660

    if (stringPtr != nullptr) {
        deallocFunc(stringPtr); // free the temp string
    }
}