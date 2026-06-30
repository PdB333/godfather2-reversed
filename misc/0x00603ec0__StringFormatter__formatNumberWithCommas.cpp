// FUNC_NAME: StringFormatter::formatNumberWithCommas

// Address: 0x00603ec0
// Role: Formats an integer string with thousands separator commas and zero-padding to a minimum width.
// The function operates on a buffer (pointed to by this+0x00) with length at this+0x04.
// It handles a leading minus sign and inserts the separator character (stored at this+0x54) every three digits.

char* StringFormatter::formatNumberWithCommas(int param_1, unsigned int minWidth)
{
    char* result;
    unsigned int length;
    int i;
    undefined4* bufferStruct; // unaff_EDI

    bufferStruct = this->buffer; // assume this is derived from param_1? Actually param_1 is likely the 'this' pointer, but the code uses unaff_EDI separately. We'll treat it as a separate pointer passed via register.
    // For reconstruction, we assume the function receives two parameters: this (param_1) and minWidth (param_2).
    // The bufferStruct is a member of the class? But the decompiler used unaff_EDI which is likely an additional register holding a pointer to the buffer struct.
    // Possibly this function is part of a static utility or a class with separate buffer pointer.
    // To match the decompiled code, we'll assume bufferStruct is a member variable (e.g., m_pBufferStruct) or a parameter passed in a register (unaff_EDI).
    // Since we don't have full context, we'll treat bufferStruct as a local variable that points to the buffer structure.

    // Actually, from the code: uVar2 = unaff_EDI[1]; local_1c = 0; so unaff_EDI points to a struct with first element string data and second element length.
    // Let's define a temporary struct for clarity.

    struct BufferInfo {
        char* data;       // +0x00
        unsigned int len; // +0x04
    };
    BufferInfo* buf = (BufferInfo*)bufferStruct;

    length = buf->len;
    int hasSign = 0;
    if ( (length != 0) && (buf->data[0] == '-') ) {
        length--;          // exclude sign from digit count
        hasSign = 1;
    }

    // Zero-pad to minimum width
    if (length < minWidth) {
        // FUN_004d4060 likely fills the buffer with '0' characters at the beginning
        fillWithChar(minWidth - length, '0');  // 0x30 = '0'
        // FUN_004d41f0 likely updates flags or resets position
        updateFlags(hasSign, 0, 0, 0);
        length = minWidth;   // actual padding done
    }

    // Insert commas every 3 digits from the right
    result = nullptr;
    if ( (length > 3) && (result = (char*)(this->separatorChar), *result != '\0') ) {
        // number of commas to insert
        int commaCount = (length - 1) / 3;
        if (commaCount != 0) {
            i = buf->len;
            // reallocate buffer to make room for commas
            result = (char*)reallocateBuffer(i + commaCount);
            for (; commaCount != 0; commaCount--) {
                i -= 3;
                // insert separator character at position i
                result = (char*)insertCharAt(buf, i);
            }
        }
    }
    return result;
}