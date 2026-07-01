// FUNC_NAME: WriteGameStateDataBlock
// Function at 0x00810c50: Writes a 16-byte data block followed by two 4-byte values into a buffer/stream, skipping the first 4 bytes (likely header or offset).
void WriteGameStateDataBlock(StreamWriter* writer, const void* data16, uint32 value1, uint32 value2)
{
    // Skip first 4 bytes (header/offset) to get a sub-writer for the payload.
    StreamWriter* payloadWriter = writer->skip(4);
    // Write 16-byte data (e.g., GUID, hash, or struct).
    payloadWriter->write(data16, 0x10);
    // Write first 4-byte value.
    payloadWriter->write(&value1, 4);
    // Write second 4-byte value.
    payloadWriter->write(&value2, 4);
}