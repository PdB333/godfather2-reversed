// FUNC_NAME: parseWideDigitSequence
// Reads up to 4 wide digit characters from a buffer starting at a given index,
// copies them to a temporary buffer, null-terminates (possibly out-of-bounds),
// and processes the extracted substring.
// Parameters:
//   pWideBuffer - pointer to a wide-character string
//   pIndex      - pointer to current index into the string (will be advanced)
void parseWideDigitSequence(const wchar_t* pWideBuffer, int* pIndex)
{
    int digitCount;
    wchar_t digitBuffer[4]; // buffer for up to 4 digits
    // Check if the current character is a wide digit
    int isDigit = _iswdigit(pWideBuffer[*pIndex]);
    for (digitCount = 0; (isDigit != 0) && (digitCount < 4); digitCount++) {
        int currentIndex = *pIndex;
        digitBuffer[digitCount] = pWideBuffer[currentIndex];
        *pIndex = currentIndex + 1;
        // Check next character
        isDigit = _iswdigit(pWideBuffer[*pIndex]);
    }
    // Null-terminate the substring (note: writes beyond array if digitCount == 4)
    digitBuffer[digitCount] = L'\0';
    // Process the extracted digit string (likely converts to integer)
    convertWideDigitsToInt(digitBuffer);
}