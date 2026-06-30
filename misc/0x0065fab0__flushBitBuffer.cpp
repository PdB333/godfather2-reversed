// FUNC_NAME: flushBitBuffer
void flushBitBuffer(void)
{
    uint totalBitCount;
    uint byteCount;
    uint headerValue;

    // DAT_01127c00 (g_bitCount) = number of pending bits in buffer
    // Check if there are enough bits to fill at least one byte (rounded up to 8)
    if ((g_bitCount + 7 & 0xfffffff8) != 0) {
        totalBitCount = g_bitCount + g_filePosition * 8;  // g_filePosition (DAT_01205a78) is byte offset in file
        // Seek to start of file and write total bit count as 4-byte header
        _fseek(g_logFile, 0, 0);
        headerValue = totalBitCount;
        _fwrite(&headerValue, 1, 4, g_logFile);
        // Seek to current byte position in file (g_filePosition)
        _fseek(g_logFile, g_filePosition, 0);
        // Write padded bytes from buffer (round up bits to bytes)
        byteCount = (g_bitCount + 7) >> 3;
        _fwrite(g_bitBuffer, 1, byteCount, g_logFile);
        _fflush(g_logFile);
        // Update pending bit count to only the low 3 bits (bits not fully written)
        g_bitCount = totalBitCount & 7;
        if (g_bitCount != 0) {
            // Keep the last byte in buffer for remaining bits
            *g_bitBuffer = g_bitBuffer[byteCount - 1];
            // Adjust file position: previous offset minus 1 plus byteCount (account for overflow?)
            g_filePosition = g_filePosition - 1 + byteCount;
            return;
        }
        // No remaining bits: just advance file position by byteCount
        g_filePosition = g_filePosition + byteCount;
        g_bitCount = 0;
    }
}