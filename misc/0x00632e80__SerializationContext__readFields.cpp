// FUNC_NAME: SerializationContext::readFields
// Function at 0x00632e80: Parses a format string and reads fields from a binary buffer into the current context.
// The format string uses single-character codes to specify field types: 'S' (string?), 'f' (float vector2?), 'l' (long/id), 'n' (name), 'u' (unsigned byte).
// param_1 (stream) is a stream object with a writable pointer at offset +0x8.
// param_2 (formatString) is a null-terminated string of field type codes.
// param_3 (count) is a flag: if zero, some fields are set to defaults; otherwise they are read from source.
// The function reads from the buffer pointed by in_EAX (sourceData) and stores results into members of the current object (this at unaff_EDI).
// Returns 1 on success, 0 if an unknown format character is encountered.

int SerializationContext::readFields(Stream* stream, const char* formatString, int count)
{
    const char* pc = formatString;
    char ch = *formatString;
    int result;
    int id;

    if (ch == '\0') {
        return 1;
    }

    do {
        switch (ch) {
        case 'S':
            // Handle string field (skip or process)
            handleStringField();
            break;

        default:
            // Unknown format character -> failure
            return 0;

        case 'f':
            // Read a 2-float vector (8 bytes) from source and write to stream buffer
            // stream->bufferPtr at offset +0x8 points to a writable location
            float* dest = *(float**)(stream + 8);
            dest[0] = sourceData[0];
            dest[1] = sourceData[1];
            break;

        case 'l':
            // Read a long/id field
            if (count == 0) {
                // Set to default (-1)
                this->m_someId = -1; // offset +0x14
            } else {
                id = generateUniqueId(); // FUN_00632aa0
                this->m_someId = id; // offset +0x14
            }
            break;

        case 'n':
            // Read a name field (string ID or pointer)
            if (count == 0) {
                result = 0;
            } else {
                result = lookupStringId(this + 4); // FUN_00633640, offset +4 is m_nameId
            }
            this->m_namePtr = result; // offset +8
            if (result == 0) {
                result = getGlobalString(); // FUN_00632da0
                this->m_nameId = result; // offset +4
                if (result == 0) {
                    this->m_namePtr = &DAT_00e2f044; // default string constant
                } else {
                    this->m_namePtr = "global";
                }
            }
            break;

        case 'u':
            // Read an unsigned byte from source and store as uint
            // sourceData[1] points to a byte at offset 7
            this->m_flags = (unsigned int)(*(unsigned char*)(sourceData[1] + 7)); // offset +0x18
            break;
        }

        ch = pc[1];
        pc++;
    } while (ch != '\0');

    return 1;
}