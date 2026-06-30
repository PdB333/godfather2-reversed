// FUNC_NAME: utility::buildTempBuffer
void buildTempBuffer(uint32_t param1, uint32_t param2) {
    int32_t outputLength = 0;
    char tempBuffer[0x1010]; // 4112-byte stack buffer (allocated via alloca_probe)
    memset(tempBuffer, 0, sizeof(tempBuffer));
    // Inner function likely serializes or formats data into the buffer,
    // but the buffer pointer is not explicitly passed in the decompiled output
    processData_603610(&outputLength, param1, param2, 0);
}