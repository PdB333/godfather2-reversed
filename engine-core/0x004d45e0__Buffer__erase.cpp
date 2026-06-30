// FUNC_NAME: Buffer::erase
int* __thiscall Buffer::erase(int pos, int count)
{
    // this->bufferPtr: pointer to data buffer (offset 0x00)
    // this->bufferSize: current length of data (offset 0x04)
    int* buffer = this;
    int currentSize = buffer[1];

    if (count != 0) {
        // If removal range extends to or beyond current size, simply truncate
        if ((uint)currentSize <= (uint)(pos + count)) {
            buffer[1] = pos;
            *(char*)(buffer[0] + pos) = '\0';
            return buffer;
        }

        // Move the tail of the buffer to fill the removed gap
        _memmove(
            (void*)(buffer[0] + pos),
            (void*)(buffer[0] + pos + count),
            (currentSize - pos) - count
        );

        // Update size and null-terminate
        buffer[1] = currentSize - count;
        *(char*)(buffer[0] + buffer[1]) = '\0';
    }

    return buffer;
}