// FUNC_NAME: BufferWriter::writeStringData

void BufferWriter::writeStringData(void)
{
    if ((*(uint *)(this + 0x4c) >> 2 & 1) == 0) {
        // First call: likely clear or reset internal buffer
        resetStringBuffer(this);
        // Second call: possibly clear a secondary buffer or re-initialize
        resetStringBuffer(this);
        *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) | 4; // Set bit 2 as initialized flag
    }

    char *str = (char *)(this + 0x84); // Offset to null-terminated string
    int len;
    if (str == nullptr) {
        len = 0;
    } else {
        // Manual strlen (string length excluding null terminator)
        char *p = str;
        while (*p != '\0') {
            p++;
        }
        len = (int)(p - (char *)(this + 0x85));
    }

    // Append string to underlying buffer (likely a packet or serialization stream)
    // params: (mode=0, string, offset=0, length)
    appendStringToBuffer(0, str, 0, len);

    // Finalize or update checksum on the buffer object at offset 0x94
    finalizeBuffer((void *)(this + 0x94));
}