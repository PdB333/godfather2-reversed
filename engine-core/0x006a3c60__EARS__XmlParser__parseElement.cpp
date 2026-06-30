// FUNC_NAME: EARS::XmlParser::parseElement
int __thiscall EARS::XmlParser::parseElement(int this, wchar_t* buffer, XmlHandler* handler, int unknown, int lineNumber)
{
    short sVar1;
    int offset;
    int count;
    int iVar3;
    int pos;
    int iVar6;
    int iVar7;
    int childPos;
    short* psVar5;
    wchar_t tagName[32]; // local_890
    wchar_t errorFormatBuffer[80]; // local_850
    wchar_t charDataBuffer[1024]; // auStack_800 (2048 bytes / 2)

    // Find first '<' in buffer
    offset = findChar(buffer, L"<");
    if (offset < 0 || buffer[offset] != L'<') {
        if (*(int*)(this + 4) != 0) {
            formatAndReportError(errorFormatBuffer, L"E01: Parse error near character %d", lineNumber);
            (*(code**)(**(int**)(this + 4) + 4))(errorFormatBuffer); // virtual call on error reporter
        }
        return -1;
    }
    offset++; // skip '<'

    // Skip whitespace after '<'
    count = skipCharacters(buffer + offset, L"> \t\n");
    if (count < 1) {
ERROR_after_open:
        pos = offset + lineNumber;
    }
    else {
        if (count + 1 > 32) { // tagName buffer size
ERROR_too_long:
            reportParseError(offset + lineNumber);
            return -1;
        }

        // Extract tag name
        _wcsncpy_s(tagName, 32, buffer + offset, count);

        // Look up handler for this tag name
        iVar3 = lookupTagName(handler, unknown, buffer + offset, count);
        offset += count;

        if (iVar3 == 0) {
            // Unknown tag: parse attributes and children without handler
            pos = parseAttributes(buffer + offset, 0, 0, offset + lineNumber);
        }
        else {
            // Known tag: notify start element
            if (*(int**)(iVar3 + 0x7c) != (int*)0) {
                (*(code**)(**(int**)(iVar3 + 0x7c) + 4))(0); // startElement callback
            }
            pos = parseAttributes(buffer + offset, iVar3 + 0x4c, *(int*)(iVar3 + 0x44), lineNumber + offset);
        }

        if (pos < 0) {
            return -1;
        }
        pos = offset + pos;

        // Check for self-closing tag />
        sVar1 = buffer[pos];
        if (sVar1 == L'/') {
            if (buffer[pos + 1] == L'>') {
                // Self-closing
                if (iVar3 != 0 && *(int**)(iVar3 + 0x80) != (int*)0) {
                    (*(code**)(**(int**)(iVar3 + 0x80) + 4))(0); // endElement callback
                }
                return pos + 2; // skip "/>"
            }
        }
        else if (sVar1 == L'>') {
            // Begin element: parse children until closing tag
            childPos = pos + 1;
            psVar5 = (short*)(buffer + childPos * 2);
            sVar1 = *psVar5;
            pos = childPos;

            while (sVar1 != 0) {
                // Skip whitespace before child
                count = skipCharacters(psVar5, L"> \t\n");
                if (count < 0) goto ERROR_generic;
                pos += count;

                // Check for closing tag </
                if (buffer[pos + 1] == L'/') break;

                // Parse child element recursively
                if (iVar3 == 0) {
                    // No handler: parse with null handler
                    count = parseElement(buffer + pos, 0, 0, pos + lineNumber);
                }
                else {
                    // Use handler's sub-element data
                    count = parseElement(buffer + pos, iVar3 + 0x5c, *(int*)(iVar3 + 0x48), lineNumber + pos);
                }

                if (count < 0) {
                    return -1;
                }
                pos += count;
                psVar5 = (short*)(buffer + pos * 2);
                sVar1 = *psVar5;
            }

            // Expecting closing tag
            count = pos + 1;
            int skipCount = skipCharacters(buffer + count, L"> \t\n");
            if (skipCount >= 0) {
                count += skipCount;
                // Compare tag name with expected closing tag
                int cmp = _wcsncmp(tagName, buffer + (pos + 2) * 2, skipCount - 1);
                if (cmp == 0 && tagName[skipCount] == L'\0') {
                    // Closing tag matches
                    skipCount = count;
                    if (buffer[count] == L'>' ||
                        ( skipCount = findChar(buffer + count, L"<"), skipCount >= 0 &&
                          (skipCount += count, buffer[skipCount] == L'>'))) {
                        // Found '>'
                        count = skipCount + 1;
                        if (iVar3 != 0) {
                            // If there was character data between tags, notify
                            int textLen = pos - childPos;
                            if (textLen > 0 && *(int*)(iVar3 + 0x40) != 0) {
                                if (textLen > 1024) goto ERROR_too_long;
                                copyString(charDataBuffer, buffer + childPos * 2, textLen);
                                (*(code**)(**(int**)(iVar3 + 0x40) + 4))(charDataBuffer); // characters callback
                            }
                            if (*(int**)(iVar3 + 0x80) != (int*)0) {
                                (*(code**)(**(int**)(iVar3 + 0x80) + 4))(0); // endElement callback
                            }
                        }
                        return count;
                    }
                }
            }
            // Fall through to error if closing tag not matched
            pos = count + lineNumber;
            goto ERROR_report;
        }
ERROR_generic:
        pos += lineNumber;
    }
ERROR_report:
    reportParseError(pos);
    return -1;
}