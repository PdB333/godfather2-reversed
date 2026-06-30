// FUNC_NAME: readPackedByte

struct PackedStream {
    char* buffer;    // +0, current read position
    short flags;     // +4, if zero -> no nibble packing, else packed mode
};

char __fastcall readPackedByte(int /* unused ECX */, PackedStream* stream)
{
    if (stream->flags == 0) {
        // Normal byte reading
        return *(stream->buffer++);
    } else {
        // Nibble-packed: combine high nibble of current byte with high nibble of next byte
        char highNibbleByte = *stream->buffer;
        uint8* nextBytePtr = (uint8*)(stream->buffer + 1);
        stream->buffer = (char*)nextBytePtr;
        return (char)((*nextBytePtr >> 4) + highNibbleByte * 0x10);
    }
}