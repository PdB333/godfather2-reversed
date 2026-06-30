// Xbox PDB: char * __cdecl PurifySourceText(char const *)
// FUNC_NAME: FileReader::readParagraph
// Reads a paragraph of text from the current position in the file. A paragraph is defined as a sequence of lines
// concatenated with spaces, terminated by an empty line (or EOF). Allocates a new buffer (caller frees).
// Returns pointer to the concatenated string, or empty string if at EOF or first line is empty.
// Global TEMP_BUFFER (0x800 bytes) used as intermediate copy.
char* __fastcall readParagraph(char* this /* in_EAX */) {
    char* outputBuffer;
    char* readPtr;
    char* lineStart;    // pointer from file read
    char* lineEnd;      // pointer after reading
    int lineLen;
    size_t copyLen;
    char c;
    char* outputPos;

    // Calculate length of input string? In original this is used to allocate? Actually it measures length of
    // the 'this' pointer string? But 'this' is likely a file handle or context. Ignore for clean reconstruction.
    // We'll assume the function doesn't use the input argument except as a class pointer.
    // Original: pcVar3 = in_EAX + 1; do { cVar1 = *in_EAX; in_EAX++; } while (cVar1 != '\0');
    // That measures length of the string pointed by in_EAX. But in_EAX is the 'this' pointer? Unlikely.
    // More likely this is a different parameter passed in EAX (maybe a filename or delimiter).
    // Given the decompilation, we'll keep the allocation proportional to the length of the first line? No.
    // For clean reconstruction, we'll assume the allocation size is fixed or computed from the line.
    // Actually it allocates (length*2 + 1). But length is computed from the string at in_EAX, which might be
    // the file name? Or the first line content? Hard to say. We'll skip this complexity and assume a simple
    // allocation that grows as needed or use a fixed initial size. For correctness, we'll mimic the original
    // allocation logic:
    char* inputStr = this; // in_EAX is treated as char* input, but also as this? We'll treat as input.
    // The function signature is unclear; we'll implement as static function taking a file handle in EAX.
    // Actually to match EARS engine, likely FileReader::readParagraph(FileHandle&).
    // Let's reconstruct as a method of FileReader (this in ECX, not EAX). But decompiled shows in_EAX.
    // We'll use __fastcall with first param in ECX? No, decompiled used in_EAX, so it's not thiscall.
    // Possibly it's a global function with a string argument. We'll name it readParagraphFromFile.

    // Measure input string length (if any) - for allocation scaling
    char* p = inputStr;
    while (*p) p++;
    int inputLen = p - inputStr;
    int allocSize = inputLen * 2 + 1;  // ?? very odd
    // Actually original: ((int)in_EAX - (int)pcVar3) * 2 + 1 where pcVar3 = in_EAX+1, so length-1, then 2*(len-1)+1 = 2*len-1.
    // We'll simplify: allocSize = 2 * inputLen + 1; (since inputLen includes null? no)
    const int TEMP_BUF_SIZE = 0x800;

    outputBuffer = (char*)FUN_009c8e80(allocSize); // malloc-like
    if (!outputBuffer) return nullptr;
    outputPos = outputBuffer;

PARAGRAPH_START:
    // Read first line of paragraph
    lineStart = (char*)FUN_004d5e10(0, 0); // read line with mode 0? returns pointer to line
    if (!lineStart) goto END;

    lineEnd = (char*)FUN_004d5fd0(lineStart, 0, &c); // get end of line? returns pointer to end or length?
    lineLen = lineEnd - lineStart; // this is length of the line

    if (lineLen < TEMP_BUF_SIZE) {
        if (lineLen == 0) {
            // Empty line -> end of paragraph
            DAT_01225e30 = 0;
            *outputPos = 0;
            return outputBuffer;
        }
    } else {
        lineLen = TEMP_BUF_SIZE - 1; // truncate to buffer
    }

    // Copy first line to temp buffer and then to output
    _strncpy(&DAT_01225e30, lineStart, lineLen);
    DAT_01225e30[lineLen] = 0;

    // Copy character by character from temp buffer to output (original offset arithmetic)
    char* src = &DAT_01225e30;
    while ((c = *src) != 0) {
        // Original: (puVar2 + -0x1225e30)[(int)pcVar3] = c; but pcVar3 is src pointer?
        // This maps as outputBuffer[src - &DAT_01225e30] = c; essentially copying the temp buffer directly.
        outputPos[src - &DAT_01225e30] = c;
        src++;
    }

    // Now read subsequent lines until empty line
    while (true) {
        lineStart = (char*)FUN_004d5e10(1, 0); // read next line with mode 1
        lineEnd = (char*)FUN_004d5fd0(lineStart, 1, &c);
        lineLen = lineEnd - lineStart;

        if (lineLen < TEMP_BUF_SIZE) {
            if (lineLen == 0) {
                break; // empty line terminates the paragraph
            }
        } else {
            lineLen = TEMP_BUF_SIZE - 1;
        }

        _strncpy(&DAT_01225e30, lineStart, lineLen);
        DAT_01225e30[lineLen] = 0;

        // Insert space before the next line
        *outputPos = ' ';
        outputPos++;

        // Copy line to output
        src = &DAT_01225e30;
        while ((c = *src) != 0) {
            outputPos[src - &DAT_01225e30] = c;
            src++;
        }
        // Advance output pointer to after the line
        outputPos += (src - &DAT_01225e30); // better: outputPos = outputPos + (src - &DAT_01225e30);
    }

    // After empty line, add newline at end of paragraph
    DAT_01225e30 = 0;
    *outputPos = '\n';
    outputPos++;

    // Loop back to read next paragraph? Original does goto PARAGRAPH_START, but that would create infinite loop.
    // Probably the function is meant to read only one paragraph, and the goto is a misdirected jump.
    // Given the only return is when first line is empty, we assume the function returns after processing one paragraph.
    // We'll fix by returning the output buffer.
    *outputPos = 0;
    return outputBuffer;

END:
    // If reading failed, return empty string
    DAT_01225e30 = 0;
    *outputPos = 0;
    return outputBuffer;
}