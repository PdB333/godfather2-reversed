// FUNC_NAME: someClass::processMessageOrCommand
void someClass::processMessageOrCommand(int param_1, int param_2, int param_3)
{
    char success;
    int *resultPtr;
    int localBuffer[3];
    code *callback;

    localBuffer[0] = 0;
    localBuffer[1] = 0;
    localBuffer[2] = 0;
    callback = (code *)0x0;
    success = FUN_008bec50(param_1, param_2, param_3, localBuffer);
    if (success != '\0') {
        resultPtr = localBuffer;
        // 0x8c0f94 likely a function pointer or static address for a handler
        FUN_0093ea90(resultPtr);
        FUN_004d3b50(localBuffer);
        FUN_00938890(param_1, param_2, 0x8c0f94, resultPtr);
    }
    if (localBuffer[0] != 0) {
        (*callback)(localBuffer[0]);
    }
    return;
}