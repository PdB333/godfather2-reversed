// FUNC_NAME: EarsConfigParser::parseTag
// Address: 0x006a3c60
// Role: Recursive XML-like tag parser. Parses opening/closing tags, attributes, and nested elements.
// Callback object (tagHandler) uses vtable offsets: +0x40 (onTagContent?), +0x44 (tagId?), +0x48 (childHandler?), +0x4c (tagData?), +0x5c (parentHandler?), +0x7c (onError?), +0x80 (onComplete?).

int __thiscall EarsConfigParser::parseTag(
    int this,               // parser context (has error callback at +0x04)
    wchar_t* input,         // wide string input
    int tagHandler,         // object handling current tag (0 if none)
    int childContext,       // context/ID for child tag creation
    int startOffset         // character offset in input where parsing starts
)
{
    short sVar1;
    int iVar2;
    rsize_t nameLength;
    int iVar3;
    int iVar4;
    short* psVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    wchar_t tagName[32];    // local_890
    char errorBuffer[80];   // local_850
    char contentBuffer[2048]; // auStack_800

    // Find position of first '<' character after startOffset
    iVar2 = findWideChar(input, L"<");
    if ((iVar2 < 0) || (*(short*)(input + iVar2 * 2) != 0x3c)) {
        // Error: expected '<'
        if (*(int*)(this + 4) != 0) {
            formatErrorString(errorBuffer, L"E01: Parse error near character %d", startOffset);
            (**(code**)(**(int**)(this + 4) + 4))(errorBuffer);
        }
        return -1;
    }
    iVar2 = iVar2 + 1; // skip '<'

    // Read tag name (until whitespace or '>' or '/>')
    nameLength = countNonDelimiter(input + iVar2 * 2, L"> \t\n");
    if ((int)nameLength < 1) {
LAB_006a3e75:
        iVar4 = iVar2 + startOffset;
    }
    else {
        if (0x20 < (int)(nameLength + 1)) {
LAB_006a3ee4:
            reportErrorPosition(iVar2 + startOffset);
            return -1;
        }
        _wcsncpy_s(tagName, 0x20, (wchar_t*)(input + iVar2 * 2), nameLength);
        // Find handler for this tag name
        iVar3 = findTagHandler(tagHandler, childContext, input + iVar2 * 2, nameLength);
        iVar2 = iVar2 + nameLength;
        if (iVar3 == 0) {
            // No handler: parse attributes directly
            iVar4 = parseTagContents(input + iVar2 * 2, 0, 0, iVar2 + startOffset);
        }
        else {
            // Handler found; invoke onError callback if present
            if (*(int**)(iVar3 + 0x7c) != (int*)0x0) {
                (**(code**)(**(int**)(iVar3 + 0x7c) + 4))(0);
            }
            // Parse attributes using tagData offset +0x4c and tagId +0x44
            iVar4 = parseTagContents(input + iVar2 * 2, iVar3 + 0x4c, *(int*)(iVar3 + 0x44), startOffset + iVar2);
        }
        if (iVar4 < 0) {
            return -1;
        }
        iVar4 = iVar2 + iVar4;
        sVar1 = *(short*)(input + iVar4 * 2);
        if (sVar1 == 0x2f) {
            // Self-closing tag: "/>"
            if (*(short*)(input + 2 + iVar4 * 2) == 0x3e) {
                if ((iVar3 != 0) && (*(int**)(iVar3 + 0x80) != (int*)0x0)) {
                    (**(code**)(**(int**)(iVar3 + 0x80) + 4))(0);
                }
                return iVar4 + 2;
            }
        }
        else if (sVar1 == 0x3e) {
            // Opening tag: '>'
            iVar8 = iVar4 + 1;
            psVar5 = (short*)(iVar8 * 2 + input);
            sVar1 = *psVar5;
            iVar4 = iVar8;
            // Parse child content until closing tag
            while (sVar1 != 0) {
                iVar2 = skipWhitespaceAndDelimiters(psVar5, &DAT_00d5d628); // skip whitespace
                if (iVar2 < 0) goto LAB_006a3e96;
                iVar4 = iVar4 + iVar2;
                iVar2 = input + iVar4 * 2;
                // Check for closing tag: "</"
                if (*(short*)(input + 2 + iVar4 * 2) == 0x2f) break;
                // Recursively parse child tag
                if (iVar3 == 0) {
                    iVar2 = parseTag(iVar2, 0, 0, iVar4 + startOffset);
                }
                else {
                    // Pass child handler from offset +0x5c and childContext from +0x48
                    iVar2 = parseTag(iVar2, iVar3 + 0x5c, *(int*)(iVar3 + 0x48), startOffset + iVar4);
                }
                if (iVar2 < 0) {
                    return -1;
                }
                iVar4 = iVar4 + iVar2;
                psVar5 = (short*)(input + iVar4 * 2);
                sVar1 = *(short*)(input + iVar4 * 2);
            }
            // Now parse closing tag
            iVar2 = iVar4 + 1; // skip '</'
            iVar6 = skipWhitespaceAndDelimiters(input + iVar2 * 2, L"> \t\n");
            if (-1 < iVar6) {
                iVar2 = iVar2 + iVar6;
                // Compare tag name with opening tag
                iVar7 = _wcsncmp(tagName, (wchar_t*)(input + (iVar4 + 2) * 2), iVar6 - 1);
                if ((iVar7 != 0) && (tagName[iVar6] == L'\0')) goto LAB_006a3e75; // imbalance?
                iVar6 = iVar2;
                // Expect '>' or '<' after tag name
                if ((*(short*)(input + iVar2 * 2) == 0x3e) ||
                    ((iVar6 = findWideChar(input + iVar2 * 2, L"<"), -1 < iVar6 &&
                    (iVar6 = iVar6 + iVar2, *(short*)(input + iVar6 * 2) == 0x3e)))) {
                    iVar2 = iVar6 + 1; // skip '>'
                    if (iVar3 != 0) {
                        if (*(int*)(iVar3 + 0x40) != 0) {
                            if (0x400 < iVar4 - iVar8) goto LAB_006a3ee4;
                            // Copy content between opening and closing tags
                            copyWideString(contentBuffer, iVar8 * 2 + input, iVar4 - iVar8);
                            (**(code**)(**(int**)(iVar3 + 0x40) + 4))(contentBuffer);
                        }
                        if (*(int**)(iVar3 + 0x80) != (int*)0x0) {
                            (**(code**)(**(int**)(iVar3 + 0x80) + 4))(0);
                        }
                    }
                    return iVar2;
                }
            }
            iVar4 = iVar2 + startOffset;
            goto LAB_006a3e7e;
        }
LAB_006a3e96:
        iVar4 = iVar4 + startOffset;
    }
LAB_006a3e7e:
    reportParseError(iVar4);
    return -1;
}