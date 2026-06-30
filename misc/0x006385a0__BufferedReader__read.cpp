// FUNC_NAME: BufferedReader::read
// Purpose: Reads a specified number of bytes from a buffered stream into a destination buffer.
// The stream is backed by a fill function that provides chunks of data. Each chunk begins with
// a control byte; if that byte is 0xFF, the read is aborted. Otherwise the chunk is consumed normally.
// Returns 0 on success, or the number of bytes remaining to be read on early termination.
// This is part of the EARS engine's streaming/network layer, likely used by TNL packet handling.
// Address: 0x006385a0
// Fields of the BufferedReader object (offsets relative to this pointer):
//   +0x00 : mRemainingBytes (uint) - number of bytes left in the current chunk
//   +0x04 : mReadPtr (byte*) - pointer to the next byte to read in the current chunk
//   +0x08 : mFillFunc (FillBufferFunc*) - function to request a new chunk
//   +0x0C : mFillParam (uint) - opaque parameter passed to mFillFunc

typedef unsigned char byte;
typedef uint unsigned int;
typedef byte* (*FillBufferFunc)(int arg0, uint arg1, uint* outSize);

unsigned int BufferedReader::read(void* dest, uint size)
{
    byte* currentReadPtr;
    uint remaining;
    uint sizeToCopy;
    byte firstByte;

    uint bytesRemainingToRead = size;  // how many bytes we still need

    if (size != 0) {
        do {
            // If no more data in the current chunk, request a new one
            if (this->mRemainingBytes == 0) {
                // Call the fill function (arg0 is always 0, arg1 is mFillParam, arg2 = &size)
                byte* newChunk = this->mFillFunc(0, this->mFillParam, &size);
                if ((newChunk == nullptr) || (size == 0)) {
                    return bytesRemainingToRead;  // abort, return remainder
                }

                // Setup new chunk: treat first byte as a control marker
                this->mReadPtr = newChunk;
                this->mRemainingBytes = size - 1;   // reserve the first byte
                firstByte = *newChunk;
                this->mReadPtr = newChunk + 1;      // skip the control byte for now

                if (firstByte == 0xFF) {            // 0xFF signals end-of-stream / error
                    return bytesRemainingToRead;
                }

                // Control byte was okay, reset to full chunk (including control byte as regular data)
                this->mRemainingBytes = size;
                this->mReadPtr = newChunk;
            }

            // Copy as much as possible from current chunk, up to needed bytes
            sizeToCopy = this->mRemainingBytes;
            if (bytesRemainingToRead < sizeToCopy) {
                sizeToCopy = bytesRemainingToRead;
            }
            memcpy(dest, this->mReadPtr, sizeToCopy);

            this->mRemainingBytes -= sizeToCopy;
            this->mReadPtr += sizeToCopy;
            dest = (void*)((int)dest + sizeToCopy);
            bytesRemainingToRead -= sizeToCopy;

        } while (bytesRemainingToRead != 0);
    }
    return 0;  // success – all bytes read
}