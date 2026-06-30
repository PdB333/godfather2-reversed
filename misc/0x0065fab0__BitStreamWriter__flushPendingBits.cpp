// FUNC_NAME: BitStreamWriter::flushPendingBits
// Purpose: Flush pending bits to file, writing total bit count to header, then pending bytes at current offset.
// Globals:
// g_bitBuffer (DAT_01127bf4): pointer to byte buffer for pending bits
// g_bitsInBuffer (DAT_01127c00): number of bits stored in buffer (0-7)
// g_bytesWritten (DAT_01205a78): byte offset in file where next write should occur
// g_outputFile (DAT_01205a70): FILE* for the stream

void BitStreamWriter::flushPendingBits()
{
    // check if there are any pending bits to flush
    if ((g_bitsInBuffer + 7) & 0xfffffff8) // effectively: g_bitsInBuffer > 0
    {
        uint totalBits = g_bitsInBuffer + g_bytesWritten * 8; // total bits written so far
        fseek(g_outputFile, 0, SEEK_SET); // seek to beginning of file to overwrite header
        fwrite(&totalBits, 1, 4, g_outputFile); // write 4-byte total bit count
        fseek(g_outputFile, g_bytesWritten, SEEK_SET); // seek to write position

        uint byteCount = (g_bitsInBuffer + 7) >> 3; // number of full bytes needed (ceil)
        fwrite(g_bitBuffer, 1, byteCount, g_outputFile); // write pending bytes
        fflush(g_outputFile);

        // update state
        g_bitsInBuffer = totalBits & 7; // remaining bits after writing full bytes
        if (g_bitsInBuffer != 0)
        {
            // keep the last written byte (which contains the partial bits) at the start of the buffer
            g_bitBuffer[0] = g_bitBuffer[byteCount - 1];
            g_bytesWritten = g_bytesWritten - 1 + byteCount; // advance write offset but account for the partial byte retained
        }
        else
        {
            g_bytesWritten = g_bytesWritten + byteCount;
            g_bitsInBuffer = 0;
        }
    }
}