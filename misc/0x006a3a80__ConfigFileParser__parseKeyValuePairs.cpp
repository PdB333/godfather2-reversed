// FUNC_NAME: ConfigFileParser::parseKeyValuePairs
int __thiscall ConfigFileParser::parseKeyValuePairs(int thisPtr, short *inputStr, undefined4 param3, undefined4 param4, int startOffset)
{
    int iVar1;
    int iVar2;
    int currentPos;
    wchar_t local_800 [1024]; // buffer for string value
    char local_850 [80]; // buffer for error message

    currentPos = 0;
    if (*inputStr != 0) {
        while (iVar1 = skipWhitespace(inputStr + currentPos, &DAT_00d5d604), -1 < iVar1) {
            currentPos = currentPos + iVar1;
            if ((inputStr[currentPos] == 0x2f) || (inputStr[currentPos] == 0x3e)) {
                return currentPos;
            }
            iVar1 = findDelimiter(inputStr + currentPos, L" \t\n=");
            if (iVar1 < 0) break;
            iVar2 = lookupKey(param3, param4, inputStr + currentPos, iVar1);
            currentPos = currentPos + iVar1;
            iVar1 = currentPos;
            if ((inputStr[currentPos] != 0x3d) &&
               ((iVar1 = skipWhitespace(inputStr, &DAT_00d5d604), iVar1 < 0 ||
                (iVar1 = iVar1 + currentPos, inputStr[iVar1] != 0x3d)))) break;
            currentPos = iVar1 + 1;
            iVar1 = skipWhitespace(inputStr + currentPos, &DAT_00d5d604);
            if (iVar1 < 0) break;
            currentPos = currentPos + iVar1;
            if ((inputStr[currentPos] != 0x22) || (iVar1 = findStringEnd(inputStr + currentPos), iVar1 < 0)) break;
            if ((iVar2 != 0) && (*(int *)(iVar2 + 0x40) != 0)) { // +0x40: callback function pointer
                if (0x400 < iVar1 + -1) {
                    reportError(currentPos + startOffset);
                    return -1;
                }
                _wcsncpy_s(local_800, 0x400, inputStr + currentPos + 1, iVar1 - 1);
                (**(code **)(**(int **)(iVar2 + 0x40) + 4))(local_800); // call callback with value
            }
            currentPos = currentPos + 1 + iVar1;
            if (inputStr[currentPos] == 0) break;
        }
    }
    if (*(int *)(thisPtr + 4) != 0) { // +0x04: error handler
        formatString(local_850, L"E01: Parse error near character %d", currentPos + startOffset);
        (**(code **)(**(int **)(thisPtr + 4) + 4))(local_850); // call error handler
    }
    return -1;
}