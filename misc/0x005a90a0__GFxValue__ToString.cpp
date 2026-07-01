// FUNC_NAME: GFxValue::ToString
char* __thiscall GFxValue::ToString(uint* this, char* outBuffer, uint bufferSize)
{
    uint typeFlag;
    int nativeData;
    uint writtenLen;
    char* resultStr;

    // Check if valid flag (bit 15) is set. If not, return empty string.
    if ((~((byte)(*this >> 0xf)) & 1) != 0) {
        resultStr = "";
        goto copyResult;
    }

    resultStr = outBuffer; // Default if no specific case overrides

    switch (*this & 0x7fff) { // lower 15 bits = type
    case 1: // String type
        resultStr = (char*)this[3]; // Pointer to internal string at offset 12
        break;

    default:
        convertUnknownType(); // FUN_005a7760
        handleTypeError();    // FUN_005ae2a0
        break;

    case 5: // Boolean type
        if (this[1] == 0) {
            resultStr = "false";
        } else {
            resultStr = "true";
        }
        goto copyResult;

    case 6: // Number (float) type
        writtenLen = convertNumberToString(this[1], outBuffer, bufferSize); // FUN_0059fd60
        if (bufferSize <= writtenLen) {
            bufferOverflowHandler(); // FUN_0059bf00
        }
        break;

    case 7: // Integer type
        writtenLen = convertIntegerToString(this[1], outBuffer, bufferSize); // FUN_0059fc50
        if (bufferSize <= writtenLen) {
            bufferOverflowHandler(); // FUN_0059bf00
        }
        break;

    case 9: // Native function type
        nativeData = getNativeFunctionData(); // FUN_005a7620
        _sprintf(outBuffer, "[native function 0x%08x]", *(undefined4*)(nativeData + 0x4c));
        if (bufferSize == 0) {
            bufferOverflowHandler(); // FUN_0059bf00
        }
        break;

    case 10: // Function type
        resultStr = "[function]";
        goto copyResult;

    case 0x15: // Sound type
        resultStr = "[sound]";
        goto copyResult;

    case 0x16: // Another type (possibly DisplayObject)
        {
            uint unknown = getSomeData(); // FUN_005a7810
            processDisplayObject(unknown); // FUN_005ab610
        }
        break;

    case 0x1b: // Object type
        resultStr = "[object]";
        goto copyResult;

    case 0x1e: // MovieClip type
        resultStr = "[MovieClip]";
        goto copyResult;
    }

    if (resultStr != (char*)0x0) {
copyResult:
        if ((outBuffer != (char*)0x0) && (bufferSize != 0)) {
            _strncpy(outBuffer, resultStr, bufferSize);
        }
    }
    return resultStr;
}