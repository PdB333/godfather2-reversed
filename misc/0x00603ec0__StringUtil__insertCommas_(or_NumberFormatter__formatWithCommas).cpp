// FUNC_NAME: StringUtil::insertCommas (or NumberFormatter::formatWithCommas)
char* __thiscall StringUtil::insertCommas(void* thisPtr, uint minWidth) // param_1 is this
{
    // Input structure (pointed by unaff_EDI) contains string pointer and length
    // This is likely a stack variable or member from the caller?
    // Actually unaff_EDI seems to be a register pointing to a string descriptor.
    // For clarity, we treat it as a local struct.
    // Offset 0: char* text, offset 4: uint textLen
    struct StringDesc {
        char* text;
        uint length;
    }* inputDesc; // assume this is passed via register (ECX or EDX?)

    char* result = nullptr;
    uint adjustedLen;
    int flagNegative = 0; // local_1c

    uint inputLen = inputDesc->length; // uVar2 = unaff_EDI[1] (offset 4)
    // local_1c = 0

    // Check for leading minus and adjust length
    if ((inputLen != 0) && (inputDesc->text[0] == '-')) {
        inputLen--;
        flagNegative = 1;
    }

    // Ensure the number part has at least minWidth digits (pad with '0')
    if (inputLen < minWidth) {
        // Allocate extra zeros ahead (function probably realloc or move)
        FUN_004d4060(minWidth - inputLen, 0x30); // allocate zeros? 0x30 = '0'
        FUN_004d41f0(flagNegative, 0, 0, 0); // possibly adjust pointer or insert prefix
        inputLen = inputLen + (minWidth - inputLen); // basically inputLen = minWidth
    }

    // Insert commas every three digits from the right
    // Only if length > 3 and the object field at +0x54 indicates commas enabled?
    // +0x54 might be a flag like "useCommaSeparator"
    if ((3 < inputLen) && (*(bool*)((int)thisPtr + 0x54) != false)) { // check flag
        // Calculate number of commas needed (roughly (len-1)/3)
        int commaCount = (inputLen - 1) / 3; // multiply by 0x55555555 trick

        if (commaCount != 0) {
            int srcIdx = inputDesc->length; // iVar3 = unaff_EDI[1]
            // Allocate space for result?
            result = (char*)FUN_004d3fe0(srcIdx + commaCount); // new buffer size

            // Insert commas by copying from original reversed?
            for (; commaCount != 0; commaCount--) {
                srcIdx -= 3; // step back three digits
                result = (char*)FUN_00401dd0(inputDesc, srcIdx); // insert comma at position
            }
        }
    }
    return result;
}