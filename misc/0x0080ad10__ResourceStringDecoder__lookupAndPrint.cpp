// FUNC_NAME: ResourceStringDecoder::lookupAndPrint
void ResourceStringDecoder::lookupAndPrint(unsigned int resourceId)
{
    char keyBuffer1[12];  // +0x00
    char keyBuffer2[12];  // +0x0C
    char resultBuffer[12]; // +0x18

    getBaseKeys(keyBuffer2, keyBuffer1); // FUN_00803330: initialize key buffers from some base
    char found = decodeResourceString(keyBuffer2, keyBuffer1, resourceId, resultBuffer); // FUN_0080a080: decode using keys
    if (found != '\0') {
        printString(resultBuffer); // FUN_008037b0: output decoded string
    }
}