// FUNC_NAME: TextTokenizer::readToken
// Reconstructed from Ghidra at 0x00638dc0.
// This function reads a token consisting of alphanumeric characters or underscores
// from an internal stream, appending characters to a dynamic buffer.
// The token is null-terminated.
// Object layout (offsets from this):
//   +0x00: mCurrentChar (int)
//   +0x24: mStream (StreamState*) - pointer to stream state
//   +0x28: mBuffer (BufferState*) - pointer to buffer state
// StreamState layout:
//   +0x00: mRemaining (int)
//   +0x04: mCurrentPtr (byte*)
//   +0x08: mReadFunc (int (*)(int, int, int*))
// BufferState layout:
//   +0x00: mData (byte*)
//   +0x04: mCapacity (int)

void TextTokenizer::readToken() {
    BufferState* buffer = (BufferState*)this->mBuffer; // +0x28
    int index = 0;

    // Ensure buffer capacity is at least 0x20
    if ((unsigned int)buffer->mCapacity < 5 && (unsigned int)buffer->mCapacity < 0x20) {
        unsigned int newSize = FUN_006279a0(buffer->mCapacity, 0x20);
        buffer->mData = (byte*)newSize;
        buffer->mCapacity = 0x20;
    }

    int minSize = 0x20; // tracks the currently required minimum capacity
    do {
        // Re-check buffer capacity and grow if needed
        buffer = (BufferState*)this->mBuffer;
        if ((unsigned int)buffer->mCapacity < (unsigned int)(minSize - 0x1b) &&
            (unsigned int)buffer->mCapacity < (unsigned int)minSize) {
            unsigned int newCap = minSize;
            if ((unsigned int)minSize < 0x20) {
                newCap = 0x20;
            }
            unsigned int newData = FUN_006279a0(buffer->mCapacity, newCap);
            buffer->mCapacity = newCap;
            buffer->mData = (byte*)newData;
        }

        // Append current character to buffer
        ((char*)buffer->mData)[index] = (char)this->mCurrentChar;
        index++;

        // Consume one byte from the stream
        StreamState* stream = (StreamState*)this->mStream; // +0x24
        int remaining = stream->mRemaining;
        stream->mRemaining = remaining - 1;

        int newChar;
        if (remaining == 0) {
            // Need more data from the stream source
            int readSize;
            byte* newData = (byte*)stream->mReadFunc(0, stream->mReadParam, &readSize);
            if (newData == (byte*)0x0 || readSize == 0) {
                newChar = 0xffffffff; // EOF marker
            } else {
                stream->mRemaining = readSize - 1;
                stream->mCurrentPtr = newData + 1; // skip the byte we already returned
                newChar = (int)*newData;
            }
        } else {
            byte* currentPtr = (byte*)stream->mCurrentPtr;
            newChar = (int)*currentPtr;
            stream->mCurrentPtr = currentPtr + 1;
        }

        this->mCurrentChar = newChar;
        minSize++;
        int isAlnum = _isalnum(newChar);
    } while (isAlnum != 0 || this->mCurrentChar == (int)'_');

    // Null-terminate the token string
    buffer = (BufferState*)this->mBuffer;
    ((char*)buffer->mData)[index] = '\0';
}