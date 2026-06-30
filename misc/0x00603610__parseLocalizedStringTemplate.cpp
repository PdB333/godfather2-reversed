// FUNC_NAME: parseLocalizedStringTemplate
void parseLocalizedStringTemplate(void* context, EAString* outputBuffer, const char* inputString, const char* endPointer)
{
    int plainTextLength = 0;
    outputBuffer->length = 0; // param_2[1] = 0
    if (outputBuffer->data) {
        outputBuffer->data[0] = '\0'; // clear string
    }
    const char* segmentStart = inputString;
    int depth = 0; // local_34
    if (inputString == nullptr) {
        return;
    }
    do {
        char c = *inputString;
        // stop if end of string or if endPointer is given and we past it
        if (c == '\0' || (endPointer != nullptr && endPointer <= inputString)) {
            break;
        }
        if (c == '\x1e') {
            depth++;
            goto processControlChar;
        }
        if (c == '\x1f') {
            depth--;
            goto processControlChar;
        }
        // Only process special markers when depth < 1
        if (depth < 1) {
            if (c == '#') {
                // Number substitution
                const char* newPos = allocateNumber(context);
                if (newPos == nullptr) {
                    // Fallback: treat as plain text
                    newPos = inputString + 1;
                    plainTextLength++;
                } else {
                    if (plainTextLength != 0) {
                        appendSubstring(segmentStart, 0, plainTextLength);
                        plainTextLength = 0;
                    }
                    // Parse number from input after '#'
                    char* endPtr = nullptr;
                    unsigned long number = _strtoul(inputString + 1, &endPtr, 10);
                    insertNumber(context, outputBuffer, number);
                    segmentStart = newPos;
                }
            } else if (c == '$') {
                // String substitution
                const char* newPos = allocateString(context);
                if (newPos == nullptr) {
                    newPos = inputString + 1;
                    plainTextLength++;
                } else {
                    if (plainTextLength != 0) {
                        appendSubstring(segmentStart, 0, plainTextLength);
                        plainTextLength = 0;
                    }
                    // Copy the variable name from input
                    stringCopy(inputString + 1, newPos);
                    insertString(context, outputBuffer);
                    segmentStart = newPos;
                }
            } else if (c == '{') {
                const char* blockEnd = getBlockEnd(context);
                if (blockEnd == nullptr) {
                    blockEnd = inputString + 1;
                    plainTextLength++;
                } else {
                    if (plainTextLength != 0) {
                        appendSubstring(segmentStart, 0, plainTextLength);
                        plainTextLength = 0;
                    }
                    if (inputString[2] == ':') {
                        // Inline command, e.g., {x:content}
                        EAString innerBuffer; // local_18
                        innerBuffer.data = nullptr;
                        innerBuffer.length = 0;
                        innerBuffer.capacity = 0;
                        innerBuffer.deleter = nullptr;
                        parseLocalizedStringTemplate(context, &innerBuffer, inputString + 3, blockEnd);
                        const char* innerData = innerBuffer.data;
                        if (innerData == nullptr) {
                            innerData = ""; // &DAT_0120546e
                        }
                        processInlineTag(inputString[1], innerData);
                        if (innerBuffer.data != nullptr) {
                            innerBuffer.deleter(innerBuffer.data); // free
                        }
                        segmentStart = blockEnd + 1;
                    } else {
                        if (inputString + 2 != blockEnd) {
                            // General expression block
                            EAString exprBuffer; // local_28
                            exprBuffer.data = nullptr;
                            exprBuffer.length = 0;
                            exprBuffer.capacity = 0;
                            exprBuffer.deleter = nullptr;
                            parseLocalizedStringTemplate(context, &exprBuffer, inputString + 1, blockEnd);
                            appendSubstring(exprBuffer.data, 0, exprBuffer.length);
                            if (exprBuffer.data != nullptr) {
                                exprBuffer.deleter(exprBuffer.data);
                            }
                        } else {
                            // Empty braces {} -> reset buffer?
                            resetOutputBuffer(outputBuffer);
                        }
                        segmentStart = blockEnd + 1;
                    }
                }
            } else {
                plainTextLength++;
                // no pointer change yet
            }
        } else {
            // Nested inside \x1e...\x1f, treat as plain text for now
            plainTextLength++;
        }
        // Move to next character
        inputString++;
        continue;

processControlChar:
        // For \x1e or \x1f, we first flush any pending plain text
        if (plainTextLength != 0) {
            appendSubstring(segmentStart, 0, plainTextLength);
            plainTextLength = 0;
        }
        // Then skip the control character and restart segment
        segmentStart = inputString + 1; // actually skip the control character
        // But careful: the loop will increment inputString after the continue,
        // so we need to adjust segmentStart here.
        // Original code: pcVar4 = param_3 + 1; local_38 = pcVar4;
        // So segmentStart points to character after control char.
        // The loop will then set param_3 = pcVar4, so effectively skip.
    } while (inputString != nullptr);

    // Flush remaining plain text
    if (plainTextLength != 0) {
        appendSubstring(segmentStart, 0, plainTextLength);
    }
}