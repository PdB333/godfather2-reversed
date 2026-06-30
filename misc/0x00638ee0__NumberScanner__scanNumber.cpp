// FUNC_NAME: NumberScanner::scanNumber
// Function at 0x00638ee0: Parses a floating-point number from an input stream (decimal and scientific notation).
// Scans digits, optional decimal point, optional exponent with sign. Outputs the number as a string into a buffer.
// This pointer (unaff_EDI) points to a context structure:
//   +0x00: currentChar (uint32_t)
//   +0x04: errorContextId (uint32_t, passed to error handlers)
//   +0x24: pointer to stream buffer (StreamBuffer)
//   +0x28: pointer to output string buffer (OutputBuffer)

void NumberScanner::scanNumber(uint32_t bLeadingDot, uint32_t errorContextId2)
{
    OutputBuffer* outBuf = reinterpret_cast<OutputBuffer*>(this->outputBuffer);
    uint32_t outBufSize = outBuf->capacity;

    // Ensure output buffer has at least 0x20 capacity; resize if needed
    if ((outBufSize < 5) || (outBufSize < 0x20))
    {
        char* newBuf = resizeBuffer(outBuf->buffer, outBufSize, 0x20);
        outBuf->buffer = newBuf;
        outBuf->capacity = 0x20;
    }

    // If a leading decimal point was already consumed, write it now
    uint32_t writePos = 0;
    if (bLeadingDot != 0)
    {
        outBuf->buffer[0] = '.';
        writePos = 1;
    }

    // ------ Integer part (digits before optional decimal point) ------
    if (isdigit(this->currentChar) != 0)
    {
        uint32_t capacityNeeded = writePos + 0x20;
        do
        {
            // Ensure buffer has room for at least capacityNeeded characters
            if ((outBuf->capacity < capacityNeeded - 0x1B) && (outBuf->capacity < capacityNeeded))
            {
                uint32_t newCap = capacityNeeded;
                if (newCap < 0x20)
                    newCap = 0x20;
                char* newBuf = resizeBuffer(outBuf->buffer, outBuf->capacity, newCap);
                outBuf->buffer = newBuf;
                outBuf->capacity = newCap;
            }

            outBuf->buffer[writePos] = static_cast<char>(this->currentChar);
            this->decrementAndFetchNextChar();
            writePos++;
            capacityNeeded++;

            if (this->checkStreamEmpty())
            {
                // Stream exhausted, fetch more
                if (!this->fetchNextCharFromStream())
                {
                    this->currentChar = 0xFFFFFFFF; // EOF
                }
            }
            else
            {
                // Advance internal pointer
                this->currentChar = this->streamBuffer->advancePointerAndRead();
            }
        } while (isdigit(this->currentChar) != 0);
    }

    uint32_t finalPos = writePos;

    // ------ Optional decimal point ------
    if (this->currentChar == '.')
    {
        outBuf->buffer[writePos] = '.';
        this->decrementAndFetchNextChar();
        writePos++;

        if (this->checkStreamEmpty())
        {
            if (!this->fetchNextCharFromStream())
                this->currentChar = 0xFFFFFFFF;
        }
        else
        {
            this->currentChar = this->streamBuffer->advancePointerAndRead();
        }

        // Check for ".." ambiguous case
        if (this->currentChar == '.')
        {
            outBuf->buffer[writePos] = '.';
            this->decrementAndFetchNextChar();
            writePos++;

            if (this->checkStreamEmpty())
            {
                if (!this->fetchNextCharFromStream())
                    this->currentChar = 0xFFFFFFFF;
            }
            else
            {
                this->currentChar = this->streamBuffer->advancePointerAndRead();
            }

            outBuf->buffer[writePos] = '\0';
            reportError("ambiguous syntax (decimal point x string concatenation)",
                        outBuf->buffer, this->errorContext);
        }
    }

    // ------ Fractional part (digits after decimal point) ------
    if (isdigit(this->currentChar) != 0)
    {
        uint32_t capacityNeeded = writePos + 0x20;
        uint32_t pos = writePos;
        do
        {
            if ((outBuf->capacity < capacityNeeded - 0x1B) && (outBuf->capacity < capacityNeeded))
            {
                uint32_t newCap = capacityNeeded;
                if (newCap < 0x20)
                    newCap = 0x20;
                char* newBuf = resizeBuffer(outBuf->buffer, outBuf->capacity, newCap);
                outBuf->buffer = newBuf;
                outBuf->capacity = newCap;
            }

            outBuf->buffer[pos] = static_cast<char>(this->currentChar);
            this->decrementAndFetchNextChar();
            pos++;
            capacityNeeded++;

            if (this->checkStreamEmpty())
            {
                if (!this->fetchNextCharFromStream())
                    this->currentChar = 0xFFFFFFFF;
            }
            else
            {
                this->currentChar = this->streamBuffer->advancePointerAndRead();
            }
            finalPos = pos;
        } while (isdigit(this->currentChar) != 0);
    }

    // ------ Optional exponent (e/E) ------
    if ((this->currentChar == 'e') || (this->currentChar == 'E'))
    {
        outBuf->buffer[finalPos] = static_cast<char>(this->currentChar);
        this->decrementAndFetchNextChar();
        if (this->checkStreamEmpty())
        {
            if (!this->fetchNextCharFromStream())
                this->currentChar = 0xFFFFFFFF;
        }
        else
        {
            this->currentChar = this->streamBuffer->advancePointerAndRead();
        }

        uint32_t expStartPos = finalPos + 1;

        // Optional exponent sign
        if ((this->currentChar == '+') || (this->currentChar == '-'))
        {
            outBuf->buffer[expStartPos] = static_cast<char>(this->currentChar);
            this->decrementAndFetchNextChar();
            if (this->checkStreamEmpty())
            {
                if (!this->fetchNextCharFromStream())
                    this->currentChar = 0xFFFFFFFF;
            }
            else
            {
                this->currentChar = this->streamBuffer->advancePointerAndRead();
            }
            expStartPos++;
        }
        finalPos = expStartPos;

        // Exponent digits
        if (isdigit(this->currentChar) != 0)
        {
            uint32_t capacityNeeded = finalPos + 0x20;
            uint32_t pos = finalPos;
            do
            {
                if ((outBuf->capacity < capacityNeeded - 0x1B) && (outBuf->capacity < capacityNeeded))
                {
                    uint32_t newCap = capacityNeeded;
                    if (newCap < 0x20)
                        newCap = 0x20;
                    char* newBuf = resizeBuffer(outBuf->buffer, outBuf->capacity, newCap);
                    outBuf->buffer = newBuf;
                    outBuf->capacity = newCap;
                }

                outBuf->buffer[pos] = static_cast<char>(this->currentChar);
                this->decrementAndFetchNextChar();
                pos++;
                capacityNeeded++;

                if (this->checkStreamEmpty())
                {
                    if (!this->fetchNextCharFromStream())
                        this->currentChar = 0xFFFFFFFF;
                }
                else
                {
                    this->currentChar = this->streamBuffer->advancePointerAndRead();
                }
                finalPos = pos;
            } while (isdigit(this->currentChar) != 0);
        }
    }

    // Null-terminate the output string
    outBuf->buffer[finalPos] = '\0';

    // Validate the number string (e.g., check for overflow, valid format)
    if (!validateNumber(outBuf->buffer, errorContextId2))
    {
        reportError("malformed number", outBuf->buffer, this->errorContext);
    }
}